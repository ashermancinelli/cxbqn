#include <cxbqn/types.hpp>

namespace cxbqn::types {

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
  auto r = dyncast<Reference>(v);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error(
        "RefArray::getref: values[idx] cast to Reference* is nullptr");
#endif
  return r;
}

}
