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

/* Takes the raw output from the compiler and constructs a compilation unit from
 * it.
 */
shared_ptr<CompUnit> deconstruct(O<Value> compiled);

struct RunResult {
  O<Value> v;
  shared_ptr<Scope> scp;
};

RunResult
run(ByteCode bc, O<Array> consts, std::vector<BlockDef> blks,
    std::vector<Body> &bds,
    std::unordered_map<std::string, uz> exported = {},
    std::optional<std::vector<std::vector<uz>>> source_indices = nullopt,
    O<Array> source = nullptr);

RunResult run(O<Value> compiled);
RunResult run(O<CompUnit> compiled);

O<Value> vm(shared_ptr<CompUnit> cu, ByteCodeRef bc, O<Array> consts, std::vector<O<Value>> stk,
            shared_ptr<Scope> scope);

O<Value> vm(shared_ptr<CompUnit> cu, shared_ptr<Scope> scope, Body b);

namespace instructions {

void setu(std::vector<O<Value>> &stk, shared_ptr<Scope>);
void setn(std::vector<O<Value>> &stk, shared_ptr<Scope>);
void setm(std::vector<O<Value>> &stk, shared_ptr<Scope>);
void setc(std::vector<O<Value>> &stk, shared_ptr<Scope>);
void varm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void varo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          shared_ptr<Scope> scp);
void fn1c(std::vector<O<Value>> &stk);
void fn1o(std::vector<O<Value>> &stk);
void fn2c(std::vector<O<Value>> &stk);
void fn2o(std::vector<O<Value>> &stk);
void dfnd(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          shared_ptr<Scope> scp, O<Array> consts);
void arro(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void arrm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk);
void md1c(std::vector<O<Value>> &stk);
void md2c(std::vector<O<Value>> &stk);
void tr2d(std::vector<O<Value>> &stk);
void tr3d(std::vector<O<Value>> &stk);
void tr3o(std::vector<O<Value>> &stk);

// Namespaces
void alim(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk, shared_ptr<CompUnit> cu);
void fldo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk, shared_ptr<CompUnit> cu);

// Headers
void seth(std::vector<O<Value>> &stk);
void pred(std::vector<O<Value>> &stk);
void vfym(std::vector<O<Value>> &stk);

} // namespace instructions

} // namespace cxbqn::vm
