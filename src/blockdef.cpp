#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

BlockDef::BlockDef(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{static_cast<bool>(immediate)},
      body_idx{idx} {
  mon_body_idxs.push_back(body_idx);
  dya_body_idxs.push_back(body_idx);
}

BlockDef::BlockDef(uz ty, uz immediate, std::vector<std::vector<uz>> indices)
    : type{static_cast<BlockType>(ty)}, immediate{
                                            static_cast<bool>(immediate)} {
  if (indices.size() != 2)
    throw std::runtime_error("BlockDef got indices with size != 2. Something "
                             "has gone horribly wrong.");
  if (indices[0].size() > 1)
    throw std::runtime_error("BlockDef got indices[0] with size > 1. Something "
                             "has gone horribly wrong.");
  if (indices[1].size() > 1)
    throw std::runtime_error("BlockDef got indices[1] with size > 1. Something "
                             "has gone horribly wrong.");

  CXBQN_DEBUG("BlockDef::BlockDef:ty={},imm={},idxs={}", ty, immediate,
              indices);

  if (indices[0].size()) {
    mon_body_idxs.push_back(indices[0][0]);
  }
  if (indices[1].size()) {
    dya_body_idxs.push_back(indices[1][0]);
  }
}

BlockDef::~BlockDef() {}

}
