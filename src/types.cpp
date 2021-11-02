#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>

namespace cxbqn::types {

Array::Array(const ByteCode::value_type N, std::deque<Value *> &stk)
    : N{static_cast<uz>(N)} {
  values.assign(stk.begin() + (stk.size() - N), stk.end());
  stk.resize(stk.size() - N);
}

std::ostream &Array::repr(std::ostream &os) const {
  os << "A<[";
  for (const auto &e : values) {
    if (e)
      e->repr(os);
    else
      os << "null";
    os << ",";
  }
  return os << "]>";
}

std::ostream &RefArray::repr(std::ostream &os) const {
  os << "RA<[";
  for (const auto &e : values) {
    if (e)
      e->repr(os);
    else
      os << "null";
    os << ",";
  }
  return os << "]>";
}

Reference *RefArray::getref(uz idx) {
#ifdef CXBQN_DEEPCHECKS
  if (idx >= N)
    throw std::runtime_error("RefArray::getref: idx >= N");
#endif
  auto *v = values[idx];
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("RefArray::getref: values[idx] is nullptr");
#endif
  auto *r = dynamic_cast<Reference *>(v);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error(
        "RefArray::getref: values[idx] cast to Reference* is nullptr");
#endif
  return r;
}

Scope::Scope(Scope *parent, std::span<Block> blks, uz blk_idx,
             std::optional<std::span<Value *>> consts)
    : blks{blks}, blk_idx{blk_idx}, vars(6, nullptr) {
  CXBQN_DEBUG("Scope::Scope");
  this->parent = parent;
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == parent and nullopt == consts)
    throw std::runtime_error("Scope::Scope: both parent=null and consts=null");
#endif
  this->consts = nullptr == parent ? consts.value() : parent->consts;
}

Value *Scope::get(Reference *r) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("Scope::get got nullptr reference");
#endif

  const auto n = r->depth;
  Scope *scp = get_nth_parent(n);

  return scp->vars[r->position_in_parent];
}

void Scope::set(bool should_var_be_set, Reference *r, Value *v) {

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
    : def{bd}, bc{bc}, bods{bods}, cached_max_nvars{nullopt} {}

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

std::pair<ByteCodeRef, uz> Block::body(u8 nargs) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);

  if (def.immediate) {
    auto bod = bods[def.body_idx];
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  if (1 == nargs) {
    auto bod = bods[def.mon_body_idxs[0]];
    CXBQN_DEBUG("Block::body:monadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  } else if (2 == nargs) {
    auto bod = bods[def.dya_body_idxs[0]];
    CXBQN_DEBUG("Block::body:dyadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  throw std::runtime_error("Block::body: unreachable");
  return std::make_pair(ByteCodeRef{}, 0);
}

bool BlockInst::imm() const {
  return this->scp->blks[this->blk_idx].def.immediate;
}

Value *BlockInst::call(u8 nargs, initl<Value *> args) {

  const auto blk = scp->blks[blk_idx];

  auto *child = new Scope(scp, scp->blks, blk_idx);

  auto [bc, nvars] = blk.body(nargs);
  std::copy(deferred_args.begin(), deferred_args.end(), child->vars.begin());
  std::copy_if(args.begin(), args.end(), child->vars.begin(),
               [](auto *v) { return nullptr != v; });

  CXBQN_DEBUG("BlockInst::call:nargs={},childscope={},blk={}", args.size(),
              *child, blk);

  std::deque<Value *> stk;

  CXBQN_DEBUG("BlockInst::call:recursing into vm");
  auto *ret = vm::vm(bc, child->consts, stk, child);
  return ret;
}

Value *Atop::call(u8 nargs, initl<Value *> args) {
  CXBQN_DEBUG("Atop::call:nargs={},args={}", nargs, args);
  auto *ret = g->call(nargs, args);
  std::copy(args.begin(), args.end(), f->deferred_args.begin());
  return f->call(nargs, {f, ret});
}

std::ostream &Atop::repr(std::ostream &os) const {
  return os << "Atop<f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g) << ">";
}

Value *Fork::call(u8 nargs, initl<Value *> args) {
  CXBQN_DEBUG("Fork::call:nargs={},args={}", nargs, args);

  // Pass 𝕩 and 𝕨 (if exists)
  std::copy(args.begin(), args.end(), f->deferred_args.begin());
  auto* l = f->call(nargs, {f});

  // Pass 𝕩 and 𝕨 (if exists)
  std::copy(args.begin(), args.end(), h->deferred_args.begin());
  auto* r = h->call(nargs, {h});

  // nargs will always be two for the inner function of a fork
  auto *ret = g->call(2, {g, r, l});

  return ret;
}

std::ostream &Fork::repr(std::ostream &os) const {
  return os << "Fork<f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g)
            << ",h=" << CXBQN_STR_NC(h) << ">";
}

} // namespace cxbqn::types
