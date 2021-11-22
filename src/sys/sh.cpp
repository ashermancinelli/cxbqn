#include "sys_helper.hpp"
namespace cxbqn::sys {
O<Value> SH::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•SH: nargs={},args={}", nargs, args);
  std::stringstream ss;

  if (nargs == 2) {
    ss << "cd " << dynamic_pointer_cast<Array>(args[2])->to_string() << "; ";
  }

  auto cmds = dynamic_pointer_cast<Array>(args[1]);
  for (auto v : cmds->values)
    ss << dynamic_pointer_cast<Array>(v)->to_string() << " ";

  std::string res = "";
  char b[128];
  std::FILE *p = popen(ss.str().c_str(), "r");

  if (!p)
    throw std::runtime_error("popen() failed!");

  while (fgets(b, sizeof b, p) != NULL)
    res += b;

  auto rc = pclose(p);

  return O<Value>(
      new Array({make_shared<Number>(rc), make_shared<Array>(res)}));
}
} // namespace cxbqn::sys
