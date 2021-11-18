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
      {1,1,0,2,0,4,17,7,0,3,0,0,26,0,3,0,0,26,11,2,33,0,0,33,0,1,12,2,48,6,34,0,1,0,1,34,0,0,17,7},
{runtime[0],runtime[15],runtime[18],runtime[50],1},
{{0,1,0},{0,1,1}},
{{0,0},{8,2}},
{{2,2,1,1,0,0,1,2,9,9,8,8,9,12,12,11,11,12,7,7,3,3,3,5,5,5,5,5,5,6,17,17,17,16,16,15,15,15,16,15},{18,18,1,1,0,0,1,18,9,9,8,8,9,12,12,11,11,12,13,13,3,3,3,5,5,5,5,5,5,6,17,17,17,16,16,15,15,15,16,15}},
std::make_shared<Array>(U"1≡{a‿b←⟨+´,+´⟩⋄a=b}")
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
