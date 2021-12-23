#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

Block::Block(BlockDef bd)
    : type{bd.type}, immediate{bd.immediate}, _body_idx{bd.body_idx},
      mon_body_idxs{bd.mon_body_idxs}, dya_body_idxs{bd.dya_body_idxs} {}

Block::Block(uz ty, uz immediate, std::vector<std::vector<uz>> indices)
    : type{static_cast<BlockType>(ty)}, immediate{
                                            static_cast<bool>(immediate)} {
  if (indices.size() != 2)
    throw std::runtime_error("BlockDef got indices with size != 2. Something "
                             "has gone horribly wrong.");

  CXBQN_DEBUG("BlockDef::BlockDef:ty={},imm={},idxs={}", ty, immediate,
              indices);

  if (indices[0].size())
    std::copy(indices[0].begin(), indices[0].end(),
              std::back_inserter(mon_body_idxs));
  if (indices[1].size())
    std::copy(indices[1].begin(), indices[1].end(),
              std::back_inserter(dya_body_idxs));
}

uz Block::body_idx(u8 nargs, uz attempt) const {
  CXBQN_DEBUG("Block::body: nargs={}", nargs);
  return immediate
             ? _body_idx
             : (1 == nargs) ? mon_body_idxs[attempt] : dya_body_idxs[attempt];
}

} // namespace cxbqn::types
