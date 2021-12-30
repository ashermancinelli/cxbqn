#include <cxbqn/config.hpp>
#include <cxbqn/namespaces/cxbqn.hpp>
#include <cxbqn/namespaces/cxbqn/plot.hpp>
#include <cxbqn/types.hpp>
#include <cxbqn/array_utils.hpp>
#include <matplotlibcpp.h>
namespace plt = matplotlibcpp;

namespace cxbqn::namespaces::cxbqn {

Plot::Plot() {
  _exported.insert({"plot", CXBQN_NEW(detail::Plot)});
  _exported.insert({"namedplot", CXBQN_NEW(detail::NamedPlot)});
  _exported.insert({"show", CXBQN_NEW(detail::Show)});
  _exported.insert({"save", CXBQN_NEW(detail::Save)});
  _exported.insert({"title", CXBQN_NEW(detail::Title)});
  _exported.insert({"legend", CXBQN_NEW(detail::Legend)});
}

O<Value> Plot::get(const std::string &n) {
  if (_exported.contains(n))
    return _exported.at(n);
  throw std::runtime_error(
      fmt::format("•cxbqn.plot: could not find name {}", n));
}

namespace detail {

O<Value> Plot::call(u8 nargs, Args &args) {
  if (1 == nargs) {
    std::vector<double> vals;
    auto x = dyncast<ArrayBase>(args[1]);
    for (int i=0; i < x->N(); i++)
      vals.push_back(dyncast<Number>(x->get(i))->v);
    plt::plot(vals);
    return CXBQN_NEW(Number, vals.size());
  } else {
    // "x" as in the x axis, not in the BQN 𝕩 sense
    auto x = dyncast<ArrayBase>(args[2]);
    std::vector<double> xv(x->N(), 0);
    for (int i = 0; i < xv.size(); i++)
      xv[i] = dyncast<Number>(x->get(i))->v;

    auto y = dyncast<ArrayBase>(args[1]);
    std::vector<double> yv(y->N(), 0);
    for (int i = 0; i < yv.size(); i++)
      yv[i] = dyncast<Number>(y->get(i))->v;

    plt::plot(xv, yv);
    return CXBQN_NEW(Number, yv.size());
  }
}

O<Value> NamedPlot::call(u8 nargs, Args &args) {
  if (1 == nargs)
    throw std::runtime_error(
        "•cxbqn.plot.NamedPlot: usage: `\"My Name\" •cxbqn.plot.NamedPlot "
        "vals`, or `\"My Name\" •cxbqn.plot.NamedPlot x‿y`");

  auto name = to_string(args[2]);
  auto plot = dyncast<ArrayBase>(args[1]);

  if (!plot->N())
    throw std::runtime_error("•cxbqn.plot.NamedPlot: empty 𝕩 not allowed");

  // If our nested type is also an array, we probably got the x‿y format
  if (t_Array == type_builtin(plot->get(0))) {
    if (plot->N() != 2)
      throw std::runtime_error(
          "•cxbqn.plot.NamedPlot: len of 𝕩 must be 1 or 2. If 2, elements of 𝕩 "
          "must be flat arrays of equal length");

    // "x" as in the x axis, not in the BQN 𝕩 sense
    auto x = dyncast<ArrayBase>(plot->get(0));
    std::vector<double> xv(x->N(), 0);
    for (int i = 0; i < xv.size(); i++)
      xv[i] = dyncast<Number>(x->get(i))->v;

    auto y = dyncast<ArrayBase>(plot->get(1));
    std::vector<double> yv(y->N(), 0);
    for (int i = 0; i < yv.size(); i++)
      yv[i] = dyncast<Number>(y->get(i))->v;

    plt::named_plot(name, xv, yv);
    return CXBQN_NEW(Number, yv.size());
  }

  std::vector<double> vals;
  for (int i=0; i<plot->N(); i++)
    vals.push_back(dyncast<Number>(plot->get(i))->v);
  plt::named_plot(name, vals);
  return CXBQN_NEW(Number, vals.size());
}

O<Value> Show::call(u8 nargs, Args &args) {
  plt::show();
  return CXBQN_NEW(Number, 1);
}

O<Value> Title::call(u8 nargs, Args &args) {
  if (2 == nargs)
    throw std::runtime_error("•cxbqn.plot.Title: only one argument");
  auto title = to_string(args[1]);
  plt::title(title);
  return CXBQN_NEW(Number, 1);
}

O<Value> Legend::call(u8 nargs, Args &args) {
  plt::legend();
  return CXBQN_NEW(Number, 1);
}

O<Value> Save::call(u8 nargs, Args &args) {
  if (2 == nargs)
    throw std::runtime_error("•cxbqn.plot.Save: only one argument");
  auto n = to_string(args[1]);
  plt::save(n);
  return CXBQN_NEW(Number, 1);
}

} // namespace detail

} // namespace cxbqn::namespaces::cxbqn
