#include <cxbqn/debug.hpp>
#include <cxbqn/scope.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

O<Value> Namespace::get(const std::string &n) {
  auto e = _scp->vars[_exported->at(n)];
  fmt::print("ns:{}->{}->{}\n", n, _exported->at(n),
             CXBQN_STR_NC(e));
  if (_exported->contains(n))
    return _scp->vars[_exported->at(n)];
  throw std::runtime_error("Namespace: could not find name");
}

O<Value> Namespace::get(uz i) { return _scp->vars[i]; }

O<Value> Namespace::set(bool should_be_set, uz n, O<Value> v) {
  auto it = std::find_if(_exported->begin(), _exported->end(),
                         [n](auto v) { return v.second == n; });
  if (it == _exported->end())
    throw std::runtime_error("namespace attempted to set unexported variable");

  auto name = (*it).second;
  return set(should_be_set, name, v);
}

O<Value> Namespace::set(bool should_be_set, const std::string &n, O<Value> v) {
  auto pos = _exported->at(n);

  bool isset = !(nullptr == _scp->vars[pos] or _scp->vars[pos]->t()[t_Nothing]);
  if (should_be_set != isset) {
    CXBQN_CRIT("should_be_set={},isset={},scp->vars={}", should_be_set, isset,
               _scp->vars);
    throw std::runtime_error(
        "Expected var to be set or unset, but this was not the case");
  }

  _scp->vars[pos] = v;
  return v;
}

} // namespace cxbqn::types
