#include <cxbqn/array_types.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <cxbqn/mem.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

uz Array::N() const {
  const auto N = values.size();
#ifdef CXBQN_DEEPCHECKS
  if (N !=
      std::accumulate(_shape.begin(), _shape.end(), 1, std::multiplies<uz>())) {
    std::stringstream ss;
    this->repr(ss);
    // for (const auto v : values)
    //{
    //  v->repr(ss);
    //  ss << ",\n";
    //}
    fmt::print("{}", ss.str());
    fmt::print("pid={}\n", getpid());
    *((int*)0);
    int i = 1;
    while (i) {
    }
    throw std::runtime_error("cxbqn internal: shape does not match values");
  }
#endif
  return N;
}

Array::Array(const uz N, std::vector<O<Value>> &stk) {
  _shape.push_back(N);
  values.assign(stk.begin() + (stk.size() - N), stk.end());
  stk.resize(stk.size() - N);
}

Array::Array(const std::string &s) {
  auto it = s.begin();
  while (it != s.end()) {
    values.push_back(O<Value>(new Character((c32)utf8::next(it, s.end()))));
  }
  _shape.push_back(values.size());
  extra_annot |= annot(t_String);
}

Array::Array(const std::u32string &s) {
//  if (U"⊢⊣˜∘○⊸⟜⊘◶"==s) {
//    fmt::print("sz={}\n",s.size());
//    throw std::runtime_error("gotcha");
//  }
  _shape.push_back(s.size());
  values.reserve(s.size());
  for (const auto &c : s)
    values.push_back(O<Value>(new Character(c)));
  extra_annot |= annot(t_String);
}

std::ostream &Array::repr(std::ostream &os) const {
  if (t()[t_String]) {
    return os << to_string(O<Value>(this));
  }
  os << "⟨sh=⟨";
  for (int i = 0; i < _shape.size(); i++) {
    os << _shape[i];
    if (i + 1 < _shape.size())
      os << ",";
  }
  os << "⟩";
  for (int i = 0; i < values.size(); i++) {
    auto e = values[i];
    if (e)
      if (t_Character == type_builtin(e)) {
        std::string s = "";
        utf8::append(dyncast<Character>(e)->c(), std::back_inserter(s));
        os << s;
      } else
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
  auto r = dyncast<Reference>(v);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error(
        "RefArray::getref: values[idx] cast to Reference* is nullptr");
#endif
  return r;
}

std::string to_string(O<Value> arr) {
  if (arr->t()[t_TypedArray]) {
    return utf8::utf32to8(dyncast<TypedArray<c32>>(arr)->values);
  } else if (t_Array == type_builtin(arr)) {
    std::string s;
    auto harr = dyncast<Array>(arr);
    for (auto v : harr->values) {
      // This hack is required to workaround the fake •_fillBy_ function
      if (nullptr == v or t_Character != type_builtin(v))
        s += " ";
      else
        utf8::append(dyncast<Character>(v)->c(), std::back_inserter(s));
    }
    return s;
  } else {
    throw std::runtime_error(
        "cxbqn internal: tried to create string from non-stringy type");
  }
}

} // namespace cxbqn::types
