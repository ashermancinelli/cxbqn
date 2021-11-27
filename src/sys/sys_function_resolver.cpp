#include "sys_helper.hpp"

namespace cxbqn::sys {

using namespace cxbqn::provides;

struct SysError : public Function {
  std::string mock = "";
  SysError(std::string m) : mock{m} {}
  O<Value> call(u8 nargs, Args args) override {
    const auto s =
        fmt::format("System Error: {} is not current available in CXBQN.\nSee "
                    "•listSys for all available system functions.",
                    mock);
    return CXBQN_NEW(Array,s);
  }
  std::ostream &repr(std::ostream &os) const override {
    return os << "•SystemError";
  }
};

static std::vector<std::string> listsys{
    "cxbqn",  "sh",  "show", "exit", "timed", "unixtime", "flines", "out",
    "import", "bqn", "fmt",  "args", "path",  "repr",     "list"};

O<Value> SystemFunctionResolver::call(u8 nargs, Args args) {
  CXBQN_DEBUG("SystemFunctionResolver: nargs={},args={}", nargs, args);
  auto x = dyncast<Array>(args[1]);
  std::vector<O<Value>> ret;

  for (int i = 0; i < x->N(); i++) {
    auto foo = dyncast<Array>(x->values[i]);
    auto s = foo->to_string();
    if ("cxbqn" == s) {
      ret.push_back(CXBQN_NEW(CXBQN));
    } else if ("show" == s) {
      ret.push_back(CXBQN_NEW(Show,_fmt));
    } else if ("listsys" == s) {
      auto ls = CXBQN_NEW(Array,listsys.size());
      for (int i = 0; i < listsys.size(); i++)
        ls->values[i] = CXBQN_NEW(Array,listsys[i]);
      ret.push_back(ls);
    } else if ("sh" == s) {
      ret.push_back(CXBQN_NEW(SH));
    } else if ("type" == s) {
      ret.push_back(CXBQN_NEW(Type));
    } else if ("decompose" == s) {
      ret.push_back(O<Value>(new Decompose(_runtime)));
    } else if ("list" == s) {
      ret.push_back(CXBQN_NEW(List));
    } else if ("exit" == s) {
      ret.push_back(CXBQN_NEW(Exit));
    } else if ("timed" == s) {
      ret.push_back(CXBQN_NEW(Timed));
    } else if ("unixtime" == s) {
      ret.push_back(CXBQN_NEW(UnixTime));
    } else if ("flines" == s) {
      ret.push_back(CXBQN_NEW(FLines));
    } else if ("out" == s) {
      ret.push_back(CXBQN_NEW(Out));
    } else if ("import" == s) {
      auto args = CXBQN_NEW(Array,2);
      args->values[0] = _runtime;
      args->values[1] = CXBQN_SHARED_FROM_THIS();
      ret.push_back(CXBQN_NEW(Import,_compiler, args));
    } else if ("bqn" == s) {
      auto args = CXBQN_NEW(Array,2);
      args->values[0] = _runtime;
      args->values[1] = CXBQN_SHARED_FROM_THIS();
      ret.push_back(CXBQN_NEW(BQN,_compiler, args));
    } else if ("fmt" == s) {
      ret.push_back(_fmt);
    } else if ("args" == s) {
      ret.push_back(_args);
    } else if ("path" == s) {
      ret.push_back(_path);
    } else if ("repr" == s) {
      ret.push_back(_repr);
    } else {
      ret.push_back(CXBQN_NEW(SysError,s));
    }
  }
  auto vret = CXBQN_NEW(Array,ret.size());
  vret->values = ret;
  return vret;
}

} // namespace cxbqn::sys
