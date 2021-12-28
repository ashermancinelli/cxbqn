#pragma once
#include <cxbqn/types.hpp>
#include <map>

namespace cxbqn::types {

struct FileNamespace : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  FileNamespace();
  O<Value> get(const std::string &n) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•file";
  }
};

struct FileLines : public Function {
  FileLines() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args& args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•file.Lines";
  }
};

struct FileList : public Function {
  FileList() {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args& args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•file.List";
  }
};

}
