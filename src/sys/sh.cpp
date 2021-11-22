#include "sys_helper.hpp"
#include <subprocess.hpp>

namespace cxbqn::sys {
O<Value> SH::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•SH: nargs={},args={}", nargs, args);

  if (nargs == 2)
    throw std::runtime_error("•SH: only monadic calls");

  auto x = dynamic_pointer_cast<Array>(args[1]);
  auto cmd = dynamic_pointer_cast<Array>(x->values[0])->to_string();
  std::vector<std::string> _args;
  for (int i = 1; i < x->N(); i++)
    _args.push_back(dynamic_pointer_cast<Array>(x->values[i])->to_string());

  auto p = subprocess::popen(cmd, _args);
  int ec = p.wait();
  std::stringstream out;
  out << p.stdout().rdbuf();
  std::stringstream err;
  err << p.stderr().rdbuf();

  return O<Value>(
      new Array({make_shared<Number>(ec), make_shared<Array>(out.str()),
                 make_shared<Array>(err.str())}));
}
} // namespace cxbqn::sys
