#pragma once
#include <cxbqn/types.hpp>
#include <map>

namespace cxbqn::namespaces::cxbqn {

struct Plot : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  Plot();
  O<Value> get(const std::string &n) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot";
  }
};

namespace detail {

struct Plot : public Function {
  Plot() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.Plot";
  }
};

struct Show : public Function {
  Show() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.Show";
  }
};

} // namespace detail

} // namespace cxbqn::namespaces::cxbqn::plot
