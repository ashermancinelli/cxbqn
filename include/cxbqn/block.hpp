#pragma once
#include <cxbqn/types.hpp>
#include <map>
#include <tuple>

namespace cxbqn::types {

enum class BlockType : u8 {
  func = 0,
  md1 = 1,
  md2 = 2,
};

struct Body {
  Body(uz offset, uz cnt) : bc_offset{offset}, var_count{cnt} {}
  uz bc_offset;
  uz var_count;
};

/**
 * \brief Blocks as they are passed from compiled output are seperate from the
 * bodies. This structure represents only the block information as passed in.
 * This type is then used to construct the true `Block` structure, which is more
 * useful at runtime.
 */
struct BlockDef {
  BlockType type;
  bool immediate;

  // FIXME: body_idx and mon/dya indices should really be a variant

  // "ambivalent index", which is used in immediate blocks
  uz body_idx;

  // list of bodies to try executing in sequence for monadic and dyadic calls
  std::vector<uz> mon_body_idxs;
  std::vector<uz> dya_body_idxs;

  BlockDef(uz ty, uz immediate, uz idx);
  BlockDef(uz ty, uz immediate, std::vector<std::vector<uz>> indices);
};

struct Block {
  BlockDef def;

  // Gives the bytecode and number of variables for a given call
  std::tuple<uz, ByteCodeRef, uz>
  body(const ByteCodeRef bc, std::span<const Body> bods, u8 nargs = 0) const;

  uz max_nvars(std::span<const Body> bods) const;

  Block(BlockDef bd);
};

} // namespace cxbqn::types
