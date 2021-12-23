#include "sys_helper.hpp"
#include <subprocess.hpp>

namespace cxbqn::sys {
O<Value> SH::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•SH: nargs={},args={}", nargs, args);

  if (nargs == 2)
    throw std::runtime_error("•SH: only monadic calls");

  auto x = dyncast<Array>(args[1]);
  auto cmd = dyncast<Array>(x->values[0])->to_string();
  std::vector<std::string> _args;
  for (int i = 1; i < x->N(); i++)
    _args.push_back(dyncast<Array>(x->values[i])->to_string());

  auto p = subprocess::popen(cmd, _args);
  int ec = p.wait();
  std::stringstream out;
  out << p.stdout().rdbuf();
  std::stringstream err;
  err << p.stderr().rdbuf();

  auto ret = CXBQN_NEW(Array, 3);
  ret->values.assign({CXBQN_NEW(Number, ec), CXBQN_NEW(Array, out.str()),
                      CXBQN_NEW(Array, err.str())});
  return ret;
}
} // namespace cxbqn::sys
