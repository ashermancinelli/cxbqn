#pragma once
#include <cstdint>
#include <cxbqn/types.hpp>
#include <memory>
#include <optional>
#include <span>
#include <tuple>
#include <variant>
#include <vector>

namespace cxbqn::vm {

using namespace cxbqn::types;

struct RunResult {
  O<Value> v;
  Scope *scp;
};

RunResult run(ByteCode bc, std::vector<O<Value>> consts,
              std::vector<BlockDef> blks, std::vector<Body> &bds);

O<Value> vm(ByteCodeRef bc, std::span<O<Value>> consts,
            std::deque<O<Value>> stk, Scope *scope);

namespace instructions {

void setu(std::deque<O<Value>> &stk, Scope *);
void setn(std::deque<O<Value>> &stk, Scope *);
void setm(std::deque<O<Value>> &stk, Scope *);
void setc(std::deque<O<Value>> &stk, Scope *);
void varm(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk);
void varo(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk, Scope *scp);
void fn1c(std::deque<O<Value>> &stk);
void fn1o(std::deque<O<Value>> &stk);
void fn2c(std::deque<O<Value>> &stk);
void fn2o(std::deque<O<Value>> &stk);
void dfnd(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk, Scope *scp);
void arro(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk);
void arrm(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk);
void md1c(std::deque<O<Value>> &stk);
void md2c(std::deque<O<Value>> &stk);
void tr2d(std::deque<O<Value>> &stk);
void tr3d(std::deque<O<Value>> &stk);
void tr3o(std::deque<O<Value>> &stk);

} // namespace instructions

} // namespace cxbqn::vm
