#pragma once
#include <cxbqn/types.hpp>
#include <map>

namespace cxbqn::namespaces::cxbqn {

struct Plot : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  Plot();
  O<Value> get(const std::string &n) override;
  std::ostream &repr(std::ostream &os) const override {
    os << "{";
    auto it = _exported.begin();
    while (it != _exported.end()) {
      os << (*it).first;
      if (++it != _exported.end())
        os << "‿";
    }
    return os << "⇐}";
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

struct NamedPlot : public Function {
  NamedPlot() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.NamedPlot";
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

struct Title : public Function {
  Title() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.Title";
  }
};

struct Legend : public Function {
  Legend() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.Legend";
  }
};

struct Save : public Function {
  Save() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn.plot.Save";
  }
};

} // namespace detail

} // namespace cxbqn::namespaces::cxbqn::plot
