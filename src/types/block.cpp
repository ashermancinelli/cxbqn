#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Block::Block(BlockDef bd)
    : type{bd.type}, immediate{bd.immediate}, _body_idx{bd.body_idx},
      mon_body_idxs{bd.mon_body_idxs}, dya_body_idxs{bd.dya_body_idxs} {}

uz Block::body_idx(u8 nargs, uz attempt) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);
  return immediate      ? _body_idx
         : (1 == nargs) ? mon_body_idxs[attempt]
                        : dya_body_idxs[attempt];
}

} // namespace cxbqn::types
