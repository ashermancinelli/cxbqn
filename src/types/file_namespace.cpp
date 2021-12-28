#include <cxbqn/file_namespace.hpp>
#include <cxbqn/fs.hpp>
#include <cxbqn/types.hpp>
#include <fstream>

namespace cxbqn::types {

FileNamespace::FileNamespace() {
  _exported.insert_or_assign("lines", CXBQN_NEW(FileLines));
  _exported.insert_or_assign("list", CXBQN_NEW(FileList));
}

O<Value> FileNamespace::get(const std::string &n) {
  if (_exported.contains(n))
    return _exported.at(n);
  throw std::runtime_error(fmt::format("file: could not find name {}", n));
}

O<Value> FileLines::call(u8 nargs, Args &args) {
  auto x = args[1];
  auto w = args[2];

  O<Array> ret;

  if (2 == nargs) {
    const auto fn = fs::path(dyncast<Array>(w)->to_string());
    const auto lines = dyncast<Array>(x);
    std::ofstream ofs(fn);
    for (const auto line : lines->values) {
      const auto linestr = dyncast<Array>(line)->to_string();
      fmt::print(ofs, "{}\n", linestr);
    }
    ofs.close();
    ret = CXBQN_NEW(Array, fs::absolute(fn));
  } else {
    ret = CXBQN_NEW(Array);
    const auto fn = fs::path(dyncast<Array>(x)->to_string());
    std::string line;
    std::ifstream ifs(fn);
    while (std::getline(ifs, line)) {
      ret->values.push_back(CXBQN_NEW(Array, line));
    }
    ret->shape.push_back(ret->values.size());
  }

  return ret;
}

O<Value> FileList::call(u8 nargs, Args &args) {
  if (2 == nargs) [[unlikely]]
    throw std::runtime_error("•file.List: only accepts one argument");
  const auto x = fs::path(dyncast<Array>(args[1])->to_string());
  auto ret = CXBQN_NEW(Array);

  for (const auto &de : fs::directory_iterator{x})
    ret->values.push_back(CXBQN_NEW(Array, de.path().filename()));

  ret->shape.push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::types
