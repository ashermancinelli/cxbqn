#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <tuple>
#include <types.hpp>
#include <variant>
#include <vector>

namespace cxbqn::vm {

using cxbqn::types::Body;
using cxbqn::types::Block;

u8 vm(std::vector<i32> bc, std::vector<u64> consts, std::vector<Block> blks,
      std::vector<Body> bodies);

} // namespace cxbqn::vm
