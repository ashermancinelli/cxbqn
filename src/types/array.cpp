#include <cxbqn/array_types.hpp>
#include <cxbqn/array_utils.hpp>
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
      std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<uz>())) {
    //std::stringstream ss;
    //this->repr(ss);
    // for (const auto v : values)
    //{
    //  v->repr(ss);
    //  ss << ",\n";
    //}
    //fmt::print("{}", ss.str());
    //fmt::print("pid={}\n", getpid()); int i = 1; while (i) { }
    throw std::runtime_error("cxbqn internal: shape does not match values");
  }
#endif
  return N;
}

Array::Array(const uz N, std::vector<O<Value>> &stk) {
  shape.push_back(N);
  values.assign(stk.begin() + (stk.size() - N), stk.end());
  stk.resize(stk.size() - N);
}

Array::Array(const std::string &s) {
  auto it = s.begin();
  while (it != s.end()) {
    values.push_back(O<Value>(new Character((c32)utf8::next(it, s.end()))));
  }
  shape.push_back(values.size());
  extra_annot |= annot(t_String);
}

Array::Array(const std::u32string &s) {
  shape.push_back(s.size());
  values.reserve(s.size());
  for (const auto &c : s)
    values.push_back(O<Value>(new Character(c)));
  extra_annot |= annot(t_String);
}

std::ostream &Array::repr(std::ostream &os) const {
  if (t()[t_String]) {
    return os << to_string((O<Value> const)this);
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

} // namespace cxbqn::types
