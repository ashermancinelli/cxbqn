#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("4≡2+⍟¯1 6") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "4≡2+⍟¯1 6");
  CompileParams p(
      {0,6,0,5,0,2,0,0,27,0,4,17,0,1,0,3,17,7},
{runtime[0],runtime[18],runtime[62],4,2,-1,6},
{{0,1,0}},
{{0,0}},
{{8,8,5,5,4,4,3,3,4,2,2,3,1,1,0,0,1,0},{8,8,6,6,4,4,3,3,4,2,2,6,1,1,0,0,1,0}},
std::make_shared<Array>(U"4≡2+⍟¯1 6")
      );
  fmt::print("startingtest\n");
  spdlog::critical("startingtest");
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
