
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Block::Block(BlockDef bd, std::span<Body> bods)
    : def{bd}, bods(bods.begin(), bods.end()), cached_max_nvars{nullopt} {}

uz Block::max_nvars() const {
  CXBQN_DEBUG("Block::max_nvars()");
  if (cached_max_nvars.has_value())
    return cached_max_nvars.value();

  if (def.immediate)
    cached_max_nvars = bods[def.body_idx].var_count;
  else {
    CXBQN_DEBUG("Block::max_nvars:getting mon body idxs");
    const auto m1 = def.mon_body_idxs.size() ? def.mon_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:getting dya body idxs");
    const auto m2 = def.dya_body_idxs.size() ? def.dya_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:mon bod idx={}, dya bod idx={}", m1, m2);
    cached_max_nvars = std::max(m1, m2);
  }

  return max_nvars();
}

std::pair<ByteCodeRef, uz> Block::body(const ByteCodeRef bc, u8 nargs) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);

  if (def.immediate) {
    auto bod = bods[def.body_idx];
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  if (1 == nargs) {
    auto bod = bods[def.mon_body_idxs[0]];
    CXBQN_DEBUG("Block::body:monadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  } else if (2 == nargs) {
    auto bod = bods[def.dya_body_idxs[0]];
    CXBQN_DEBUG("Block::body:dyadic bodies:offset={},nvars={}", bod.bc_offset,
                bod.var_count);
    const auto _bc = bc.subspan(bod.bc_offset);
    return std::make_pair(_bc, bod.var_count);
  }

  throw std::runtime_error("Block::body: unreachable");
  return {};
}
 
}
