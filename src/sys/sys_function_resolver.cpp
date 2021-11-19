#include "sys_helper.hpp"

namespace cxbqn::sys {

struct SysError : public Function {
  std::string mock = "";
  SysError(std::string m) : mock{m} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override {
    const auto s = fmt::format("System Error: {} is not current available in CXBQN", mock);
    throw std::runtime_error(s);
    return bi_Nothing();
  }
  std::ostream &repr(std::ostream &os) const override {
    return os << "•SystemError";
  }
};

O<Value> SystemFunctionResolver::call(u8 nargs, std::vector<O<Value>> args) {
  auto x = dynamic_pointer_cast<Array>(args[1]);
  auto ret = make_shared<Array>(x->values.size());

  for (auto _s : x->values) {
    auto s = dynamic_pointer_cast<Array>(_s)->to_string();
    if (false) {

    } else if ("open" == s) {

    } else {
      ret->values.push_back(make_shared<SysError>(s));
    }
  }

  return ret;
}

} // namespace cxbqn::sys
