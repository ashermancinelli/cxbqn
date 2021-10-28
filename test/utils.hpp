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
  std::vector<Value*> v;
  Consts(initl<i32> i) {
    for (const auto& e : i)
      v.push_back(new Number{static_cast<cxbqn::f64>(e)});
  }
};

struct CompileParams {
    std::vector<i32> bc;
    Consts consts;
    std::vector<Block> blks;
    std::vector<Body> bodies;
};
