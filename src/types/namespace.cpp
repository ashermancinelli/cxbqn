#include <cxbqn/types.hpp>
#include <cxbqn/scope.hpp>

namespace cxbqn::types {

O<Value> Namespace::get(const std::string& n) {
  if (_exported->contains(n))
    return _scp->vars[_exported->at(n)];
  throw std::runtime_error("Namespace: could not find name");
}

O<Value> Namespace::get(uz i) {
  return _scp->vars[i];
}

}
