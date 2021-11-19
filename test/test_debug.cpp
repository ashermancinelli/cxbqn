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
  spdlog::critical("test='{}'", "+˜⁼7");
  CompileParams p(
      {0,3,0,2,0,1,0,0,26,26,16,7},
{runtime[0],runtime[45],runtime[49],7},
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
  CHECK(3.5 == doctest::Approx(n->v));
}
