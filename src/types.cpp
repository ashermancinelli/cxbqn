#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>

namespace cxbqn::types {

Array::Array() : values{nullptr} {}

Array::Array(initl<f64> vs) {
  shape.push_back(vs.size());
  values = new f64[vs.size()];
  std::copy(vs.begin(), vs.end(), values);
}

Array::Array(initl<uz> szs, initl<f64> vs) {
  std::copy(szs.begin(), szs.end(), std::back_inserter(shape));
  uz len = std::accumulate(szs.begin(), szs.end(), 1, std::multiplies<uz>());
  values = new f64[len];
  std::copy(vs.begin(), vs.end(), values);
}

Array::~Array() {
  if (nullptr != values)
    delete[] values;
}

Scope::Scope(Scope *parent, std::span<Block> blks, uz blk_idx)
    : blks{blks}, blk_idx{blk_idx} {
  CXBQN_DEBUG("Scope::Scope()");
  this->parent = parent;
  this->vars.resize(6 + blks[blk_idx].max_nvars());
  for (auto e : vars)
    e = nullptr;
}

Value *Scope::get(Reference *r) {

  // CXBQN_DEBUG_NC("Scope::get(ref={})", r);

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

  CXBQN_DEBUG("Scope::set:r->pos={},scp->vars.size={}", r->position_in_parent,
              scp->vars.size());

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
    CXBQN_DEBUG("BlockDef:mondaic body index={}", mon_body_idxs[0]);
  }
  if (indices[1].size()) {
    dya_body_idxs.push_back(indices[1][0]);
    CXBQN_DEBUG("BlockDef:dyadic body index={}", dya_body_idxs[0]);
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
    if (nargs != 0)
      throw std::runtime_error("immediate body invoked with arguments");
    auto bod = bods[def.body_idx];
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  if (1 == nargs) {
    // segfault here
    auto bod = bods[def.mon_body_idxs[0]];
    CXBQN_DEBUG("Block::body:offset={},nvars={}", bod.bc_offset, bod.var_count);
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  } else if (2 == nargs) {
    auto bod = bods[def.dya_body_idxs[0]];
    CXBQN_DEBUG("Block::body:offset={},nvars={}", bod.bc_offset, bod.var_count);
    auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  throw std::runtime_error("Block::body: unreachable");
  return std::make_pair(ByteCodeRef{}, 0);
}

Value *UserFn::call(uz nargs, Value *w, Value *x) {
  auto *child = new Scope(scp, scp->blks, blk_idx);
  const auto blk = scp->blks[blk_idx];
  CXBQN_DEBUG("UserFn::call:nargs={},childscope={},blk={}", nargs, *child, blk);

  auto [bc, nvars] = blk.body(nargs);

  /* From the spec:
   *
   * A frame is a mutable list of slots for variable values. It has slots for
   * any special names that are available during the blocks execution followed
   * by the local variables it defines. Special names use the ordering 𝕤𝕩𝕨𝕣𝕗𝕘.
   */
  child->vars[0] = this;
  if (nargs > 0) {
    CXBQN_DEBUG_NC("UserFn::call:x={}", x);
    child->vars[1] = x;
  }
  if (nargs > 1) {
    CXBQN_DEBUG_NC("UserFn::call:w={}", w);
    child->vars[2] = w;
  }

  // idk what to do about this. I still don't understand the relationship
  // between the scope's frame and the consts I pass in.
  std::vector<Value *> consts(3 + blk.max_nvars(), nullptr);

  std::deque<Value *> stk;

  CXBQN_DEBUG("UserFn::call:recursing into vm");
  auto *ret = vm::vm(bc, consts, stk, child);
  return ret;
}

} // namespace cxbqn::types
