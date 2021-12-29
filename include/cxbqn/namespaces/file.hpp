#pragma once
#include <cxbqn/types.hpp>
#include <cxbqn/fs.hpp>
#include <map>

namespace cxbqn::namespaces {

using namespace cxbqn::types;

struct File : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  File(std::string root);
  O<Value> get(const std::string &n) override;
  std::ostream &repr(std::ostream &os) const override {
    os << "{";
    auto it = _exported.begin();
    while(it != _exported.end()) {
      os << (*it).first;
      if (++it != _exported.end())
        os << "‿";
    }
    return os << "⇐}";
  }
};

struct FileLines : public Function {
  FileLines(std::string root) : root{root} {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args& args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•file.Lines";
  }
  fs::path root;
};

struct FileList : public Function {
  FileList(std::string root) : root{root} {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args& args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•file.List";
  }
  fs::path root;
};

}
