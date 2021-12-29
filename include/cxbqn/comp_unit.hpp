#pragma once
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/types.hpp>
#include <cxbqn/mem.hpp>

namespace cxbqn::types {

struct CompUnit : public Marked {
  ByteCode _bc;
  O<ArrayBase> _consts;
  std::vector<Block> _blocks;
  std::vector<Body> _bodies;
  std::vector<std::string> _namelist;
  std::unordered_map<std::string, uz> _exported;
};

} // namespace cxbqn::types
