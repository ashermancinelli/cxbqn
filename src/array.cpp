#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Array::Array(const uz N, std::vector<O<Value>> &stk) {
  shape.push_back(N);
  values.assign(stk.begin() + (stk.size() - N), stk.end());
  stk.resize(stk.size() - N);
}

std::ostream &Array::repr(std::ostream &os) const {
  if (t()[t_String]) {
    std::string s;
    for (const auto e : values)
      utf8::append(std::dynamic_pointer_cast<const Character>(e)->c(), s);
    return os << "\"" << s << "\"";
  }
  os << "⟨sh=⟨";
  for (int i = 0; i < shape.size(); i++) {
    os << shape[i];
    if (i + 1 < shape.size())
      os << ",";
  }
  os << "⟩";
  for (int i = 0; i < values.size(); i++) {
    auto e = values[i];
    if (e)
      e->repr(os);
    else
      os << "null";
    if (i + 1 < values.size())
      os << ",";
  }
  return os << "⟩";
}

std::ostream &RefArray::repr(std::ostream &os) const {
  os << "r⟨";
  for (int i = 0; i < values.size(); i++) {
    auto e = values[i];
    if (e)
      e->repr(os);
    else
      os << "null";
    if (i + 1 < values.size())
      os << ",";
  }
  return os << "⟩";
}

O<Reference> RefArray::getref(uz idx) {
#ifdef CXBQN_DEEPCHECKS
  if (idx >= N())
    throw std::runtime_error("RefArray::getref: idx >= N");
#endif
  auto v = values[idx];
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("RefArray::getref: values[idx] is nullptr");
#endif
  auto r = std::dynamic_pointer_cast<Reference>(v);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error(
        "RefArray::getref: values[idx] cast to Reference* is nullptr");
#endif
  return r;
}

}
