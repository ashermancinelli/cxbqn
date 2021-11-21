#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Import::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•Import: nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Import: can only be called with one arg");

  auto x = dynamic_pointer_cast<Array>(args[1]);
  if (!x)
    throw std::runtime_error("•Import: 𝕩 must be a string");

  auto w =
      2 == nargs ? dynamic_pointer_cast<Array>(args[2]) : make_shared<Array>(0);

  auto f = fs::path(x->to_string());
  if (!fs::exists(f))
    throw std::runtime_error("•Import path does not exist");

  // auto sys_func_rslvr = make_shared<SystemFunctionResolver>(*_compw)
  O<Array> src;
  std::string _src = "";
  if (std::FILE *fp = std::fopen(f.c_str(), "r")) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      _src += ch;
    }
    std::fclose(fp);
    fmt::print("{}\n", _src);
    src.reset(new Array(_src));
  } else {
    throw std::runtime_error("•Import: could not open path");
  }

  auto compiled = _compiler->call(2, {_compiler, src, _compiler_args});

  auto ret = vm::run(compiled);

  return ret.v;
}

} // namespace cxbqn::sys

