#pragma once
#include <cxbqn/types.hpp>
#include <map>

namespace cxbqn::types {

struct CXBQNNamespace : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  CXBQNNamespace();
  O<Value> get(const std::string &n) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "•cxbqn";
  }
};

}
