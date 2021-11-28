#pragma once
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

struct CompUnit {
  ByteCode _bc;
  O<Array> _consts;
  std::vector<Block> _blocks;
  std::vector<Body> _bodies;
  std::vector<std::string> _namelist;
  std::unordered_map<std::string, uz> _exported;
};

} // namespace cxbqn::types
