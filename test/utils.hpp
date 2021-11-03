#pragma once
#include <cxbqn/cxbqn.hpp>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

/**
 *
 * Testing utilities for parsing output from ccxx.bqn.
 *
 */

struct Consts {
  std::vector<Value *> v;
  Consts(std::initializer_list<std::variant<Value*, i32>> i) {
    for (const auto &e : i) {
      if (std::holds_alternative<Value*>(e))
        v.push_back(std::get<Value*>(e));
      else
        v.push_back(new Number{static_cast<cxbqn::f64>(std::get<i32>(e))});
    }
  }
};

struct CompileParams {
  std::vector<i32> bc;
  Consts consts;
  std::vector<BlockDef> blk_defs;
  std::vector<Body> bodies;
};

#define CXBQN_LOG_TESTN(N) spdlog::critical("=== Test #" #N " ===");
