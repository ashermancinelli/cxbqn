#pragma once
#include <cstdint>
#include <cxbqn/types.hpp>
#include <deque>
#include <memory>
#include <optional>
#include <span>
#include <tuple>
#include <variant>
#include <vector>

namespace cxbqn::vm {

using cxbqn::types::Block;
using cxbqn::types::Body;
using cxbqn::types::Scope;
using cxbqn::types::Value;

struct RunResult {
  Value *v;
  Scope *scp;
};

RunResult run(std::vector<i32> bc, std::vector<Value *> consts,
              std::vector<Block> blks, std::vector<Body> bodies);

Value *vm(std::vector<i32> bc, std::vector<Value *> consts, Block blk,
          Body body, std::deque<Value *> stk, Scope *scope);

namespace instructions {

void setn(std::deque<Value *> stk, Scope *);

}

} // namespace cxbqn::vm
