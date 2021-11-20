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
  CXBQN_DEBUG("SystemFunctionResolver: nargs={},args={}", nargs, args);
  auto x = dynamic_pointer_cast<Array>(args[1]);
  std::vector<O<Value>> ret;

  for (int i=0; i < x->N(); i++) {
    auto foo = dynamic_pointer_cast<Array>(x->values[i]);
    auto s = foo->to_string();
    if ("cxbqn" == s) {
      ret.push_back(make_shared<CXBQN>());
    } else if ("show" == s) {
      ret.push_back(make_shared<Show>());
    } else if ("timed" == s) {
      ret.push_back(make_shared<Timed>());
    } else if ("unixtime" == s) {
      ret.push_back(make_shared<UnixTime>());
    } else {
      ret.push_back(make_shared<SysError>(s));
    }
  }
  auto vret = make_shared<Array>(ret.size());
  vret->values = ret;
  return vret;
}
O<Value> bi_SystemFunctionResolver() {
  static SystemFunctionResolver s;
  return O<Value>(&s, [](auto*){});
}

} // namespace cxbqn::sys
