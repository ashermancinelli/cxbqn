#include <provides.hpp>
#include <spdlog/spdlog.h>

namespace cxbqn::provides {

Value *Type::operator()(Value *x) {
  spdlog::debug("•Type x");
  return new types::Number(x->t());
}

Value *Type::operator()(Value *, Value *) {
  throw std::runtime_error("no dyadic •Type");
}

Value* Plus::operator()(Value*w, Value*x) {
  using types::Number;
  spdlog::debug("w+x");
  assert(w->t()==1);
  assert(x->t()==1);
  return new Number(dynamic_cast<Number*>(w)->v + dynamic_cast<Number*>(x)->v);
}

Value* Plus::operator()(Value*x) {
  spdlog::critical("no monadic + yet");
  assert(false);
}

} // namespace cxbqn::provides
