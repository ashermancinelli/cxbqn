#pragma once
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

struct CompUnit {
  ByteCode _bc;
  std::vector<Block> _blocks;
  std::vector<Body> _bodies;
  O<Array> _consts;
  static O<CompUnit> from_raw(O<Value> compiled);
  static O<CompUnit> from_raw(CompileParams p);
};

}
