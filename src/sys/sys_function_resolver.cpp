#include "sys_helper.hpp"

namespace cxbqn::sys {

using namespace cxbqn::provides;

struct SysError : public Function {
  std::string mock = "";
  SysError(std::string m) : mock{m} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override {
    const auto s =
        fmt::format("System Error: {} is not current available in CXBQN.\nSee "
                    "•listSys for all available system functions.",
                    mock);
    return make_shared<Array>(s);
  }
  std::ostream &repr(std::ostream &os) const override {
    return os << "•SystemError";
  }
};

static std::vector<std::string> listsys{
    "cxbqn",  "sh",  "show", "exit", "timed", "unixtime", "flines", "out",
    "import", "bqn", "fmt",  "args", "path",  "repr",     "list"};

O<Value> SystemFunctionResolver::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("SystemFunctionResolver: nargs={},args={}", nargs, args);
  auto x = dynamic_pointer_cast<Array>(args[1]);
  std::vector<O<Value>> ret;

  for (int i = 0; i < x->N(); i++) {
    auto foo = dynamic_pointer_cast<Array>(x->values[i]);
    auto s = foo->to_string();
    if ("cxbqn" == s) {
      ret.push_back(make_shared<CXBQN>());
    } else if ("show" == s) {
      ret.push_back(make_shared<Show>());
    } else if ("listsys" == s) {
      auto ls = make_shared<Array>(listsys.size());
      for (int i = 0; i < listsys.size(); i++)
        ls->values[i] = make_shared<Array>(listsys[i]);
      ret.push_back(ls);
    } else if ("sh" == s) {
      ret.push_back(make_shared<SH>());
    } else if ("type" == s) {
      ret.push_back(make_shared<Type>());
    } else if ("decompose" == s) {
      ret.push_back(O<Value>(new Decompose(_runtime)));
    } else if ("list" == s) {
      ret.push_back(make_shared<List>());
    } else if ("exit" == s) {
      ret.push_back(make_shared<Exit>());
    } else if ("timed" == s) {
      ret.push_back(make_shared<Timed>());
    } else if ("unixtime" == s) {
      ret.push_back(make_shared<UnixTime>());
    } else if ("flines" == s) {
      ret.push_back(make_shared<FLines>());
    } else if ("out" == s) {
      ret.push_back(make_shared<Out>(_fmt));
    } else if ("import" == s) {
      auto args = make_shared<Array>(2);
      args->values[0] = _runtime;
      args->values[1] = shared_from_this();
      ret.push_back(make_shared<Import>(_compiler, args));
    } else if ("bqn" == s) {
      auto args = make_shared<Array>(2);
      args->values[0] = _runtime;
      args->values[1] = shared_from_this();
      ret.push_back(make_shared<BQN>(_compiler, args));
    } else if ("fmt" == s) {
      ret.push_back(_fmt);
    } else if ("args" == s) {
      ret.push_back(_args);
    } else if ("path" == s) {
      ret.push_back(_path);
    } else if ("repr" == s) {
      ret.push_back(_repr);
    } else {
      ret.push_back(make_shared<SysError>(s));
    }
  }
  auto vret = make_shared<Array>(ret.size());
  vret->values = ret;
  return vret;
}

} // namespace cxbqn::sys
