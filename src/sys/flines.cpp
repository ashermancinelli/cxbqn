#include "sys_helper.hpp"
#include <fstream>

namespace cxbqn::sys {

O<Value> FLines::call(u8 nargs, Args args) {
  CXBQN_DEBUG("•FLines: nargs={},args={}", nargs, args);
#ifdef CXBQN_DEEPCHECKS
  if (2 == nargs)
    throw std::runtime_error("•FLines can only accept one arg");
#endif
  auto x = args[1];
  auto pth = fs::path(dyncast<Array>(x)->to_string());
  std::ifstream f(pth.c_str());
  auto ret = CXBQN_NEW(Array,0);
  for (std::string line; std::getline(f, line); )
    ret->values.push_back(CXBQN_NEW(Array,line));
  ret->shape[0] = ret->values.size();
  return ret;
}

}
