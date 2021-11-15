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
  O<Scope> scp;
};

RunResult run(ByteCode bc, std::vector<O<Value>> consts,
              std::vector<BlockDef> blks, std::vector<Body> &bds,
              std::optional<std::vector<std::vector<uz>>> source_indices=nullopt,
              O<Array> source=nullptr);

O<Value> vm(ByteCodeRef bc, std::vector<O<Value>> consts,
            std::vector<O<Value>> stk, O<Scope> scope);

namespace instructions {

void setu(std::vector<O<Value>> &stk, O<Scope>);
void setn(std::vector<O<Value>> &stk, O<Scope>);
void setm(std::vector<O<Value>> &stk, O<Scope>);
void setc(std::vector<O<Value>> &stk, O<Scope>);
void varm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void varo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          O<Scope> scp);
void fn1c(std::vector<O<Value>> &stk);
void fn1o(std::vector<O<Value>> &stk);
void fn2c(std::vector<O<Value>> &stk);
void fn2o(std::vector<O<Value>> &stk);
void dfnd(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          O<Scope> scp);
void arro(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void arrm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void md1c(std::vector<O<Value>> &stk);
void md2c(std::vector<O<Value>> &stk);
void tr2d(std::vector<O<Value>> &stk);
void tr3d(std::vector<O<Value>> &stk);
void tr3o(std::vector<O<Value>> &stk);

} // namespace instructions

} // namespace cxbqn::vm
