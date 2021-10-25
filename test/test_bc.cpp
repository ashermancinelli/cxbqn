#include <cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

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

CompileParams t0{
#include <bc_tests/t0.hpp>
};
// #include <bc_tests/all.hpp>

TEST_CASE("Bytecode", "") {
  SECTION("") {

  }
}
