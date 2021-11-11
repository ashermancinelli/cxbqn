#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <utf8.h>

namespace cxbqn::types {

O<Value> bi_Nothing() {
  static Nothing n;
  return std::shared_ptr<Nothing>(&n, [](Nothing *) {});
}

Array::Array(const uz N, std::deque<O<Value>> &stk) {
  shape.push_back(N);
  values.assign(stk.begin() + (stk.size() - N), stk.end());
  stk.resize(stk.size() - N);
}

std::ostream &Array::repr(std::ostream &os) const {
  if (t()[t_String]) {
    std::string s;
    for (const auto e : values)
      utf8::append(std::dynamic_pointer_cast<const Character>(e)->c(), s);
    return os << "\"" << s << "\"";
  }
  os << "⟨sh=⟨";
  for (int i = 0; i < shape.size(); i++) {
    os << shape[i];
    if (i + 1 < shape.size())
      os << ",";
  }
  os << "⟩";
  for (int i = 0; i < values.size(); i++) {
    auto e = values[i];
    if (e)
      e->repr(os);
    else
      os << "null";
    if (i + 1 < values.size())
      os << ",";
  }
  return os << "⟩";
}

std::ostream &RefArray::repr(std::ostream &os) const {
  os << "r⟨";
  for (int i = 0; i < values.size(); i++) {
    auto e = values[i];
    if (e)
      e->repr(os);
    else
      os << "null";
    if (i + 1 < values.size())
      os << ",";
  }
  return os << "⟩";
}

O<Reference> RefArray::getref(uz idx) {
#ifdef CXBQN_DEEPCHECKS
  if (idx >= N())
    throw std::runtime_error("RefArray::getref: idx >= N");
#endif
  auto v = values[idx];
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("RefArray::getref: values[idx] is nullptr");
#endif
  auto r = std::dynamic_pointer_cast<Reference>(v);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error(
        "RefArray::getref: values[idx] cast to Reference* is nullptr");
#endif
  return r;
}

Scope::Scope(Scope *parent, std::vector<Block> blks, uz blk_idx,
             std::optional<std::vector<O<Value>>> consts)
    : blks{blks}, blk_idx{blk_idx} {
  CXBQN_DEBUG("Scope::Scope");
  this->parent = parent;
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == parent and nullopt == consts)
    throw std::runtime_error("Scope::Scope: both parent=null and consts=null");
#endif
  this->consts = nullptr == parent ? consts.value() : parent->consts;
  vars.resize(6 + blks[blk_idx].max_nvars());
  std::fill(vars.begin(), vars.end(), nullptr);
}

O<Value> Scope::get(O<Reference> r) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("Scope::get got nullptr reference");
#endif

  const auto n = r->depth;
  Scope *scp = get_nth_parent(n);

  return scp->vars[r->position_in_parent];
}

void Scope::set(bool should_var_be_set, O<Reference> r, O<Value> v) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == v)
    throw std::runtime_error("assign: got nullptr value");
#endif

  const auto n = r->depth;
  CXBQN_DEBUG("Scope::set:shoudbeset={},depth={}", should_var_be_set, n);
  auto *scp = get_nth_parent(n);
  CXBQN_DEBUG_NC("Scope::set:nth parent={}", scp);

  CXBQN_DEBUG("Scope::set:r->pos={},scp->vars={}", r->position_in_parent,
              scp->vars);

  bool isset = nullptr != scp->vars[r->position_in_parent];
  if (should_var_be_set != isset) {
    CXBQN_CRIT("should_var_be_set={},isset={}", should_var_be_set, isset);
    throw std::runtime_error(
        "Expected var to be set or unset, but this was not the case");
  }

  // assign to the underlying value
  scp->vars[r->position_in_parent] = v;
}

Scope *Scope::get_nth_parent(uz depth) {
  CXBQN_DEBUG("Scope::get_nth_parent:depth={}", depth);
  auto *scp = this;
  while (depth-- > 0) {
    CXBQN_DEBUG("Scope::get_nth_parent:traversing to parent. depth={}", depth);
    CXBQN_DEBUG_NC("before={}", scp);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp->parent)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
    scp = scp->parent;
    CXBQN_DEBUG_NC("after={}", scp);
  }
  return scp;
}

BlockDef::BlockDef(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{static_cast<bool>(immediate)},
      body_idx{idx} {
  mon_body_idxs.push_back(body_idx);
  dya_body_idxs.push_back(body_idx);
}

BlockDef::BlockDef(uz ty, uz immediate, std::vector<std::vector<uz>> indices)
    : type{static_cast<BlockType>(ty)}, immediate{
                                            static_cast<bool>(immediate)} {
  if (indices.size() != 2)
    throw std::runtime_error("BlockDef got indices with size != 2. Something "
                             "has gone horribly wrong.");
  if (indices[0].size() > 1)
    throw std::runtime_error("BlockDef got indices[0] with size > 1. Something "
                             "has gone horribly wrong.");
  if (indices[1].size() > 1)
    throw std::runtime_error("BlockDef got indices[1] with size > 1. Something "
                             "has gone horribly wrong.");

  CXBQN_DEBUG("BlockDef::BlockDef:ty={},imm={},idxs={}", ty, immediate,
              indices);

  if (indices[0].size()) {
    mon_body_idxs.push_back(indices[0][0]);
  }
  if (indices[1].size()) {
    dya_body_idxs.push_back(indices[1][0]);
  }
}

BlockDef::~BlockDef() {}

Block::Block(std::span<i32> bc, BlockDef bd, std::span<Body> bods)
    : def{bd}, bc(bc.begin(), bc.end()),
      bods(bods.begin(), bods.end()), cached_max_nvars{nullopt} {}

uz Block::max_nvars() const {
  CXBQN_DEBUG("Block::max_nvars()");
  if (cached_max_nvars.has_value())
    return cached_max_nvars.value();

  if (def.immediate)
    cached_max_nvars = bods[def.body_idx].var_count;
  else {
    CXBQN_DEBUG("Block::max_nvars:getting mon body idxs")
    const auto m1 = def.mon_body_idxs.size() ? def.mon_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:getting dya body idxs")
    const auto m2 = def.dya_body_idxs.size() ? def.dya_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:mon bod idx={}, dya bod idx={}", m1, m2);
    cached_max_nvars = std::max(m1, m2);
  }

  return max_nvars();
}

std::pair<ByteCode, uz> Block::body(u8 nargs) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);

  if (def.immediate) {
    auto bod = bods[def.body_idx];
    const auto _bc = ByteCode(bc.begin() + bod.bc_offset, bc.end());
    return std::make_pair(_bc, bod.var_count);
  }

  if (1 == nargs) {
    auto bod = bods[def.mon_body_idxs[0]];
    CXBQN_DEBUG("Block::body:monadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = ByteCode(bc.begin() + bod.bc_offset, bc.end());
    return std::make_pair(_bc, bod.var_count);
  } else if (2 == nargs) {
    auto bod = bods[def.dya_body_idxs[0]];
    CXBQN_DEBUG("Block::body:dyadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = ByteCode(bc.begin() + bod.bc_offset, bc.end());
    return std::make_pair(_bc, bod.var_count);
  }

  throw std::runtime_error("Block::body: unreachable");
  return std::make_pair(ByteCode{}, 0);
}

bool BlockInst::imm() const {
  return this->scp->blks[this->blk_idx].def.immediate;
}

O<Value> BlockInst::call(u8 nargs, std::vector<O<Value>> args) {

  const auto blk = scp->blks[blk_idx];

  auto *child = new Scope(scp, scp->blks, blk_idx);

  auto [bc, nvars] = blk.body(nargs);
  std::copy(args.begin(), args.end(), child->vars.begin());

  CXBQN_DEBUG("BlockInst::call:nargs={},childscope={},blk={}", args.size(),
              *child, blk);

  std::deque<O<Value>> stk;

  CXBQN_DEBUG("BlockInst::call:recursing into vm");
  auto ret = vm::vm(bc, child->consts, stk, child);
  CXBQN_DEBUG("BlockInst::call:returning {}", CXBQN_STR_NC(ret));

  return ret;
}

O<Value> Atop::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Atop::call:nargs={},args={}", nargs, args);
  auto ret = g->call(nargs, args);

  return f->call(nargs, {f, ret, bi_Nothing()});
}

std::ostream &Atop::repr(std::ostream &os) const {
  return os << "(atop f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g) << ")";
}

O<Value> Fork::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Fork::call:nargs={},args={}", nargs, args);

  // Pass 𝕩 and 𝕨 (if exists)
  args[0] = h;
  auto r = h->call(nargs, args);

  args[0] = f;
  auto l = f->call(nargs, args);

  // nargs will always be two for the inner function of a fork
  auto ret = g->call(2, {g, r, l});

  return ret;
}

std::ostream &Fork::repr(std::ostream &os) const {
  return os << "(fork f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g)
            << ",h=" << CXBQN_STR_NC(h) << ")";
}

O<Value> Md1Deferred::call(u8 nargs, std::vector<O<Value>> args) {
  args.push_back(m1);
  args.push_back(f);
  return m1->call(nargs, args);
}
std::ostream &Md1Deferred::repr(std::ostream &os) const {
  fmt::print(os, "{}{}", CXBQN_STR_NC(f), CXBQN_STR_NC(m1));
  return os;
}

O<Value> Md2Deferred::call(u8 nargs, std::vector<O<Value>> args) {
  args.push_back(m2);
  args.push_back(f);
  args.push_back(g);
  return m2->call(nargs, args);
}

std::ostream &Md2Deferred::repr(std::ostream &os) const {
  fmt::print(os, "{}{}{}", CXBQN_STR_NC(f), CXBQN_STR_NC(m2), CXBQN_STR_NC(g));
  return os;
}

} // namespace cxbqn::types
