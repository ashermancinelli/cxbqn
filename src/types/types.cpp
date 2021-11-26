#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

O<Value> bi_Nothing() {
  static Nothing n;
#ifdef CXBQN_MEM_shared_ptr
  return std::shared_ptr<Nothing>(&n, [](Nothing *) {});
#elif CXBQN_MEM_leak
  return &n;
#else
#error "unsupported"
#endif
}

O<Value> Atop::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Atop::call:nargs={},args={}", nargs, args);
  auto ret = g->call(nargs, {g, args[1], args[2]});
  return f->call(1, {f, ret, bi_Nothing()});
}

std::ostream &Atop::repr(std::ostream &os) const {
  return os << "(atop f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g) << ")";
}

O<Value> Fork::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Fork::call:nargs={},args={}", nargs, args);

  // Pass 𝕩 and 𝕨 (if exists)
  std::vector<O<Value>> rargs{h, args[1],
                              (2 == nargs ? args[2] : bi_Nothing())};
  auto r = h->call(nargs, rargs);

  std::vector<O<Value>> largs{f, args[1],
                              (2 == nargs ? args[2] : bi_Nothing())};
  auto l = f->call(nargs, largs);

  // nargs will always be two for the inner function of a fork
  auto ret = g->call(2, {g, r, l});

  return ret;
}

std::ostream &Fork::repr(std::ostream &os) const {
  return os << "(fork f=" << CXBQN_STR_NC(f) << ",g=" << CXBQN_STR_NC(g)
            << ",h=" << CXBQN_STR_NC(h) << ")";
}

O<Value> Md1Deferred::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Md1Deferred::call(after adding 𝕣, 𝕗):nargs={},args={}", nargs,
              args);

  return m1->call(nargs, {m1, args[1], args[2], CXBQN_SHARED_FROM_THIS(), f});
}
std::ostream &Md1Deferred::repr(std::ostream &os) const {
  fmt::print(os, "( md1D {} {} )", CXBQN_STR_NC(f), CXBQN_STR_NC(m1));
  return os;
}

O<Value> Md2Deferred::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Md1Deferred::call(after adding 𝕣, 𝕗, 𝕘):nargs={},args={}", nargs,
              args);
  return m2->call(nargs, {m2, args[1], args[2], CXBQN_SHARED_FROM_THIS(), f, g});
}

std::ostream &Md2Deferred::repr(std::ostream &os) const {
  fmt::print(os, "( md2D {} {} {})", CXBQN_STR_NC(f), CXBQN_STR_NC(m2), CXBQN_STR_NC(g));
  return os;
}

} // namespace cxbqn::types
