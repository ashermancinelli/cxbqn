#include <cxbqn/config.hpp>
#include <cxbqn/namespaces/cxbqn.hpp>
#include <cxbqn/namespaces/cxbqn/plot.hpp>
#include <cxbqn/types.hpp>
#include <matplotlibcpp.h>
namespace plt = matplotlibcpp;

namespace cxbqn::namespaces::cxbqn {

Plot::Plot() {
  _exported.insert({"plot", CXBQN_NEW(detail::Plot)});
  _exported.insert({"show", CXBQN_NEW(detail::Show)});
}

O<Value> Plot::get(const std::string &n) {
  if (_exported.contains(n))
    return _exported.at(n);
  throw std::runtime_error(fmt::format("•cxbqn.plot: could not find name {}", n));
}

namespace detail {

O<Value> Plot::call(u8 nargs, Args &args) {
  std::vector<double> vals;
  auto x = dyncast<Array>(args[1]);
  for (const auto e : x->values)
    vals.push_back(dyncast<Number>(e)->v);
  plt::plot(vals);
  return CXBQN_NEW(Number, vals.size());
}

O<Value> Show::call(u8 nargs, Args &args) {
  plt::show();
  return CXBQN_NEW(Number, 1);
}

} // namespace detail

} // namespace cxbqn::namespaces::cxbqn
