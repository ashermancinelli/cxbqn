#pragma once
#include <cxbqn/types.hpp>
#include <map>

namespace cxbqn::namespaces {

using namespace cxbqn::types;

struct CXBQN : public BuiltinNamespace {
  std::unordered_map<std::string, O<Value>> _exported;
  CXBQN();
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

}
