#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;


TEST_CASE("grade") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯1‿0‿1‿3 ≡ -⟜(+´÷≠)⌾(3⊸↑)↕4");
  CompileParams p(
      {0,15,0,6,16,0,5,0,8,0,14,27,0,10,0,3,0,2,0,7,0,0,26,21,0,9,0,1,27,27,16,0,4,0,11,0,12,0,13,0,14,11,4,17,7},
{runtime[0],runtime[1],runtime[3],runtime[14],runtime[18],runtime[26],runtime[28],runtime[50],runtime[55],runtime[56],runtime[57],-1,0,1,3,4},
{{0,1,0}},
{{0,0}}
      );
  fmt::print("startingtest\n");
  spdlog::critical("startingtest");
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
