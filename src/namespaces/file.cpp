#include <cxbqn/namespaces/file.hpp>
#include <cxbqn/fs.hpp>
#include <cxbqn/types.hpp>
#include <cxbqn/array_types.hpp>
#include <cxbqn/array_utils.hpp>
#include <fstream>

namespace cxbqn::namespaces {

using namespace cxbqn::types;

File::File(std::string root) {
  _exported.insert_or_assign("lines", CXBQN_NEW(FileLines, root));
  _exported.insert_or_assign("list", CXBQN_NEW(FileList, root));
}

O<Value> File::get(const std::string &n) {
  if (_exported.contains(n))
    return _exported.at(n);
  throw std::runtime_error(fmt::format("file: could not find name {}", n));
}

O<Value> FileLines::call(u8 nargs, Args &args) {
  auto x = args[1];
  auto w = args[2];

  if (2 == nargs) {
    const auto fn = [=, r = root] () -> fs::path {
      auto n = to_string(w);
      if (!n.size())
        throw std::runtime_error("•file.Lines: got empty filename");
      if (n[0] == '/')
        return n;
      return r / n;
    }();
    const auto lines = dyncast<Array>(x);
    std::ofstream ofs(fn);
    for (const auto line : lines->values) {
      const auto linestr = to_string(line);
      fmt::print(ofs, "{}\n", linestr);
    }
    ofs.close();
    return CXBQN_NEW(Array, fs::absolute(fn));
  } else {
    auto ret = CXBQN_NEW(Array);
    const auto fn = [=, r = this->root] () -> fs::path {
      auto n = to_string(x);
      if (!n.size())
        throw std::runtime_error("•file.Lines: got empty filename");
      if (n[0] == '/')
        return n;
      return r / n;
    }();
    std::string line;
    std::ifstream ifs(fn);
    while (std::getline(ifs, line)) {
      ret->values.push_back(CXBQN_NEW(Array, line));
    }
    ret->shape.push_back(ret->values.size());
    return ret;
  }
}

O<Value> FileList::call(u8 nargs, Args &args) {
  if (2 == nargs) [[unlikely]]
    throw std::runtime_error("•file.List: only accepts one argument");
  const auto x = [=, arg = args[1], r = this->root] () -> fs::path {
    auto n = to_string(arg);
    if (!n.size())
      throw std::runtime_error("•file.List: got empty filename");
    if (n[0] == '/')
      return n;
    return r / n;
  }();
  auto ret = CXBQN_NEW(Array);

  for (const auto &de : fs::directory_iterator{x})
    ret->values.push_back(CXBQN_NEW(Array, de.path().filename()));

  ret->shape.push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::types
