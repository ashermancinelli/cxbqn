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
  Value *v;
  Scope *scp;
};

RunResult run(ByteCode bc, std::vector<Value *> consts,
              std::vector<BlockDef> blks, std::vector<Body> bds);

Value *vm(ByteCodeRef bc, std::span<Value *> consts, std::deque<Value *> stk,
          Scope *scope);

namespace instructions {

void setu(std::deque<Value *> &stk, Scope *);
void setn(std::deque<Value *> &stk, Scope *);
void setm(std::deque<Value *> &stk, Scope *);
void setc(std::deque<Value *> &stk, Scope *);
void varm(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk);
void varo(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp);
void fn1c(std::deque<Value *> &stk);
void fn1o(std::deque<Value *> &stk);
void fn2c(std::deque<Value *> &stk);
void fn2o(std::deque<Value *> &stk);
void dfnd(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp);
void arro(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk);
void arrm(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk);
void md1c(std::deque<Value *> &stk);
void md2c(std::deque<Value *> &stk);
void tr2d(std::deque<Value *> &stk);
void tr3d(std::deque<Value *> &stk);
void tr3o(std::deque<Value *> &stk);

} // namespace instructions

} // namespace cxbqn::vm
