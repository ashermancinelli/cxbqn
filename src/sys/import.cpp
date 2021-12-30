#include "sys_helper.hpp"
#include <cxbqn/array_utils.hpp>
#include <cstdlib>
#include <cxbqn/config.hpp>

namespace {
static inline auto resolve_bqnpath(const fs::path &p) -> fs::path {
  auto const *e = std::getenv("BQNPATH");
  if (nullptr == e)
    return "";

  // : delimited environment var
  const auto bqnpath = std::string(e);
  uz start = 0, end;
  std::string elem;
  fs::path pelem;

  // Try to split by ':' first
  while ((end = bqnpath.find(':', start)) != std::string::npos) {
    elem = bqnpath.substr(start, end-start);
    if (fs::exists(pelem = (fs::path(elem) / p)))
      return pelem;
    start = end+1;
  }

  // Check the last element of BQNPATH
  elem = bqnpath.substr(start);
  if (fs::exists(pelem = (fs::path(elem) / p)))
    return pelem;

  // If no : was found, maybe it's a single path and we can just return that
  if (bqnpath.size() and fs::exists(pelem = (bqnpath / p)))
    return pelem;

  // Try the CXBQN installation prefix as well
  if (fs::exists(pelem = (fs::path(CXBQN_INSTALL_PREFIX) / p)))
    return pelem;

  // Otherwise, just resolve to the default directory
  return fs::path("/usr/share/bqn") / p;
}
} // namespace

namespace cxbqn::sys {

O<Value> Import::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•Import: nargs={},args={}", nargs, args);

  const auto x = [=] {
    const auto xx = dyncast<ArrayBase>(args[1]);
    if (!xx)
      throw std::runtime_error("•Import: 𝕩 must be a string");
    const auto s = to_string(xx);
    if (!s.size())
      throw std::runtime_error("•Import: got empty 𝕩");
    return s;
  }();

  auto w = [=] () -> O<Array> {
    if (1 == nargs)
      return CXBQN_NEW(Array);
    auto war = dyncast<ArrayBase>(args[2]);
    return CXBQN_NEW(Array, values(war), war->shape);
  }();

  const auto f = [=, path = fs::path(to_string(_path)), &x]() -> fs::path {
    // We got an absolute path
    if ('/' == x[0])
      return x;

    // Otherwise, use relative path based on directory of script
    const auto relative = path / fs::path(x);
    if (fs::exists(relative))
      return relative;

    const auto from_bqnpath = resolve_bqnpath(x);
    if (fs::exists(from_bqnpath))
      return from_bqnpath;

    const auto err = fmt::format("•Import: path {} does not exist", x);
    throw std::runtime_error(err);
  }();

  const auto src = [&f]() -> O<Array> {
    std::FILE *fp = std::fopen(f.c_str(), "r");
    if (!fp)
      throw std::runtime_error("•Import: could not open path");

    std::string _src = "";
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      _src += ch;
    }
    std::fclose(fp);

    return CXBQN_NEW(Array, _src);
  }();

  auto sys_func_rslvr =
      CXBQN_NEW(SystemFunctionResolver, w, _fmt, _repr, _compiler, _bqnruntime,
                CXBQN_NEW(Array, f.parent_path()));

  auto compw = CXBQN_NEW(Array, 2);
  compw->values[0] = _bqnruntime;
  compw->values[1] = sys_func_rslvr;

  Args a{_compiler, src, compw};
  auto compiled = _compiler->call(2, a);

  auto ret = vm::run(compiled);

  return ret.v;
}

} // namespace cxbqn::sys
