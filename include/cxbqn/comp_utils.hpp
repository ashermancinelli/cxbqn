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
  std::vector<O<Value>> v;
  Consts(std::initializer_list<std::variant<O<Value>, i32, f64>> i) {
    for (auto &e : i) {
      if (std::holds_alternative<O<Value>>(e))
        v.push_back(std::get<O<Value>>(e));
      else if (std::holds_alternative<f64>(e))
        v.push_back(std::make_shared<Number>(std::get<f64>(e)));
      else
        v.push_back(std::make_shared<Number>(
            static_cast<cxbqn::f64>(std::get<i32>(e))));
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
