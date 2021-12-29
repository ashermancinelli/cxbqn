#include <cxbqn/array_utils.hpp>
#include <sstream>

namespace cxbqn::types {

std::vector<O<Value>> values(O<ArrayBase> const arr) {
  if (arr->t()[t_TypedArray]) {
    std::vector<O<Value>> v;
    for (int i=0; i < arr->N(); i++)
      v.push_back(arr->get(i));
    return v;
  } else {
    return dyncast<Array>(arr)->values;
  }
}

std::string to_string(O<Value> const v) {
  if (v->t()[t_C32Array]) {
    return utf8::utf32to8(dyncast<TypedArray<c32>>(v)->values);
  } else if (t_Array == type_builtin(v)) {
    std::string s;
    auto harr = dyncast<Array>(v);
    for (auto v : harr->values) {
      // This hack is required to workaround the fake •_fillBy_ function
      if (nullptr == v or t_Character != type_builtin(v))
        s += " ";
      else
        utf8::append(dyncast<Character>(v)->c(), std::back_inserter(s));
    }
    return s;
  } else {
    std::stringstream ss;
    v->repr(ss);
    return ss.str();
  }
}
}
