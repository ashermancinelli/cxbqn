#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Block::Block(BlockDef bd) : def{bd} {}

uz Block::max_nvars(std::span<const Body> bods) const {
  CXBQN_DEBUG("Block::max_nvars()");
  if (def.immediate)
    return bods[def.body_idx].var_count;
  else {
    CXBQN_DEBUG("Block::max_nvars:getting mon body idxs");
    const auto m1 = def.mon_body_idxs.size() ? def.mon_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:getting dya body idxs");
    const auto m2 = def.dya_body_idxs.size() ? def.dya_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:mon bod idx={}, dya bod idx={}", m1, m2);
    return std::max(m1, m2);
  }
}

std::tuple<uz, ByteCodeRef, uz> Block::body(const ByteCodeRef bc,
                                       std::span<const Body> bods, u8 nargs) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);

  if (def.immediate) {
    auto bod = bods[def.body_idx];
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_tuple(bod.bc_offset, _bc, bod.var_count);
  }

  if (1 == nargs) {
    auto bod = bods[def.mon_body_idxs[0]];
    CXBQN_DEBUG("Block::body:monadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_tuple(bod.bc_offset, _bc, bod.var_count);
  } else if (2 == nargs) {
    auto bod = bods[def.dya_body_idxs[0]];
    CXBQN_DEBUG("Block::body:dyadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_tuple(bod.bc_offset, _bc, bod.var_count);
  }

  throw std::runtime_error("Block::body: unreachable");
}

} // namespace cxbqn::types
