#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Import::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•Import: nargs={},args={}", nargs, args);

  auto x = dyncast<Array>(args[1]);
  if (!x)
    throw std::runtime_error("•Import: 𝕩 must be a string");

  auto w = 2 == nargs ? dyncast<Array>(args[2]) : CXBQN_NEW(Array);

  auto f = fs::path(x->to_string());
  if (!fs::exists(f))
    throw std::runtime_error("•Import path does not exist");

  std::FILE *fp = std::fopen(f.c_str(), "r");
  if (!fp)
    throw std::runtime_error("•Import: could not open path");

  std::string _src = "";
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    _src += ch;
  }
  std::fclose(fp);
  auto src = CXBQN_NEW(Array, _src);

  auto sys_func_rslvr = CXBQN_NEW(SystemFunctionResolver, w, _fmt, _repr,
                                  _compiler, _bqnruntime, _path);

  auto compw = CXBQN_NEW(Array, 2);
  compw->values[0] = _bqnruntime;
  compw->values[1] = sys_func_rslvr;

  Args a{_compiler, src, compw};
  auto compiled = _compiler->call(2, a);

  auto ret = vm::run(compiled);

  return ret.v;
}

} // namespace cxbqn::sys

