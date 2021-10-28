#include <provides.hpp>
#include <cxbqn_debug.hpp>

namespace cxbqn::provides {

Value *Type::operator()(Value *x) {
  CXBQN_DEBUG("•Type x");
  return new types::Number(x->t());
}

Value *Type::operator()(Value *, Value *) {
  throw std::runtime_error("no dyadic •Type");
  return nullptr;
}

Value* Plus::operator()(Value*w, Value*x) {
  using types::Number;
  CXBQN_DEBUG("provides:w+x");
  assert(w->t()==1);
  assert(x->t()==1);
  return new Number(dynamic_cast<Number*>(w)->v + dynamic_cast<Number*>(x)->v);
}

Value* Plus::operator()(Value*x) {
  CXBQN_DEBUG("no monadic + yet");
  return nullptr;
}

} // namespace cxbqn::provides
