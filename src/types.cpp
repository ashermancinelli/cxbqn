#include <types.hpp>

namespace cxbqn::types {

Block::Block(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{immediate}, comp{nullptr},
      body_idx{idx} {}

Block::~Block() {}

#define EXPLICIT_INSTANTIATE(TYPE) template struct Array<TYPE>;
CXBQN_FOR_ALL_TS(EXPLICIT_INSTANTIATE);
#undef EXPLICIT_INSTANTIATE

} // namespace cxbqn::types
