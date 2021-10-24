#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <tuple>
#include <types.hpp>
#include <variant>
#include <vector>
#include <span>

namespace cxbqn::vm {

using cxbqn::types::Value;
using cxbqn::types::Body;
using cxbqn::types::Block;

u8 vm(std::vector<i32> bc, std::vector<Value*> consts, std::vector<Block> blks,
      std::vector<Body> bodies);

} // namespace cxbqn::vm
