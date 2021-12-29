#include "sys_helper.hpp"
#include <subprocess.hpp>

namespace cxbqn::sys {
O<Value> SH::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•SH: nargs={},args={}", nargs, args);

  if (nargs == 2)
    throw std::runtime_error("•SH: only monadic calls");

  auto x = dyncast<ArrayBase>(args[1]);
  auto cmd = to_string(x->get(0));
  std::vector<std::string> _args;
  for (int i = 1; i < x->N(); i++)
    _args.push_back(to_string(x->get(i)));

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
