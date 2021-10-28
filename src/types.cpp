#include <cxbqn/debug.hpp>
#include <cxbqn/types.hpp>

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

Scope::Scope(Scope *parent, Block blk, Body bdy) {
  CXBQN_DEBUG("types::Scope()");
  this->parent = parent;
  this->vars.resize(bdy.var_count);
  std::fill(vars.begin(), vars.end(), nullptr);
}

Value *Scope::get(Reference *r) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("Scope::get got nullptr reference");
#endif

  Scope *scp = this;
  auto n = r->depth;
  while (n--) {
    scp = scp->parent;
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
  }

  CXBQN_DEBUG("cxbqn::Scope::get:r->pos={}", r->position_in_parent);
#ifdef CXBQN_DEEPCHECKS
  if (r->position_in_parent >= scp->vars.size())
    throw std::runtime_error("Attempted to retrieve value of reference in "
                             "location outside of bounds "
                             "in the intended scope");
#endif
  return scp->vars[r->position_in_parent];
}

void Scope::set(Reference *r, Value *v) {
  // Number of scopes to ascend
  auto n = r->depth;
  CXBQN_DEBUG("cxbqn::vm::instructions::assign:n={}", n);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == v)
    throw std::runtime_error("assign: got nullptr value");
#endif

  Scope *scp = this;

  // Walk the scope descendence to find the target scope
  while (n--) {
    scp = scp->parent;
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
  }

  CXBQN_DEBUG("cxbqn::Scope::set:r->pos={}", r->position_in_parent);
#ifdef CXBQN_DEEPCHECKS
  if (r->position_in_parent >= scp->vars.size())
    throw std::runtime_error(
        "Attempted to assign value to reference in location outside of bounds "
        "in the intended scope");
#endif

  // assign to the underlying value
  scp->vars[r->position_in_parent] = v;
}

Block::Block(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{static_cast<bool>(immediate)},
      comp{nullptr}, body_idx{idx} {}

Block::~Block() {}

} // namespace cxbqn::types
