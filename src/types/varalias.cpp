#include <cxbqn/types.hpp>

namespace cxbqn::types {

O<Value> VarAlias::set(bool should_be_set, O<Value> v) {
  _ns->set(should_be_set, _name, v);
  return v;
}

}
