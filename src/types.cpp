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
  CXBQN_DEBUG("types::Scope()");
  this->parent = parent;
  this->vars.resize(blks[blk_idx].var_count);
  for (auto e : vars)
    e = new Nothing();
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

  const auto n = r->depth;
  CXBQN_DEBUG("cxbqn::vm::instructions::assign:n={}", n);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == v)
    throw std::runtime_error("assign: got nullptr value");
#endif

  Scope *scp = get_nth_parent(n);

  bool isset =
      nullptr == dynamic_cast<Nothing *>(scp->vars[r->position_in_parent]);
  if (should_var_be_set != isset) {
    CXBQN_CRIT("should_var_be_set={},isset={}", should_var_be_set, isset);
    throw std::runtime_error(
        "Expected var to be set or unset, but this was not the case");
  }

  // assign to the underlying value
  scp->vars[r->position_in_parent] = v;
}

Scope *Scope::get_nth_parent(uz depth) {
  auto *scp = this;
  while (depth--) {
    CXBQN_DEBUG("Scope::set: traversing to parent");
    scp = scp->parent;
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
  }
  return scp;
}

BlockDef::BlockDef(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{static_cast<bool>(immediate)},
      body_idx{idx} {}

BlockDef::~BlockDef() {}

Block::Block(std::span<i32> bc, BlockDef bd, std::span<Body> bods)
    : immediate{bd.immediate}, type{bd.type} {
  const auto body = bods[bd.body_idx];
  this->bc = bc.subspan(body.bc_offset);
  this->var_count = body.var_count;
}

Value *UserFn::call(uz nargs, Value *w, Value *x) {
  auto *child = new Scope(scp, scp->blks, blk_idx);
  const auto blk = scp->blks[scp->blk_idx];
  CXBQN_DEBUG("UserFn::call:nargs={},childscope={},blk={}", nargs, *child, blk);

  /* From the spec:
   *
   * A frame is a mutable list of slots for variable values. It has slots for
   * any special names that are available during the blocks execution followed
   * by the local variables it defines. Special names use the ordering 𝕤𝕩𝕨𝕣𝕗𝕘.
   */
  std::vector<Value *> consts(3 + blk.var_count, nullptr);
  consts[0] = this;
  if (nargs > 1) consts[2] = w;
  if (nargs > 0) consts[1] = x;

  std::deque<Value *> stk;

  CXBQN_DEBUG("UserFn::call:recursing into vm");
  auto* ret = vm::vm(scp->blks[scp->blk_idx].bc, consts, stk, child);
  return ret;
}

} // namespace cxbqn::types
