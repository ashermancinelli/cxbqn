#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <deque>
#include <span>
#include <tuple>
#include <types.hpp>
#include <variant>
#include <vector>

namespace cxbqn::vm {

using cxbqn::types::Block;
using cxbqn::types::Body;
using cxbqn::types::Value;

Value *vm(std::vector<i32> bc, std::vector<Value *> consts,
          std::vector<Block> blks, std::vector<Body> bodies,
          std::deque<Value *> stk);

} // namespace cxbqn::vm
