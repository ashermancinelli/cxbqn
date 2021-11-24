#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Block::Block(BlockDef bd)
    : type{bd.type}, immediate{bd.immediate}, _body_idx{bd.body_idx},
      mon_body_idxs{bd.mon_body_idxs}, dya_body_idxs{bd.dya_body_idxs} {}

uz Block::max_nvars(std::span<const Body> bods) const {
  CXBQN_DEBUG("Block::max_nvars()");
  if (immediate)
    return bods[_body_idx].var_count;
  else {
    CXBQN_DEBUG("Block::max_nvars:getting mon body idxs");
    const auto m1 = mon_body_idxs.size() ? mon_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:getting dya body idxs");
    const auto m2 = dya_body_idxs.size() ? dya_body_idxs[0] : 0;
    CXBQN_DEBUG("Block::max_nvars:mon bod idx={}, dya bod idx={}", m1, m2);
    return std::max(m1, m2);
  }
}

uz Block::body_idx(u8 nargs, uz attempt) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);
  return immediate      ? _body_idx
         : (1 == nargs) ? mon_body_idxs[attempt]
                        : dya_body_idxs[attempt];
}

} // namespace cxbqn::types
