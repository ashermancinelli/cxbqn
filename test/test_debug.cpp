#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("'a'≡⟨⟩⊑'a'") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨7,7‿7,7⟩≡⟨⟨⟩,⟨⟨⟩,⟨⟩⟩,⟨⟩⟩⊑<7");
  CompileParams p(
      {0,17,0,16,0,13,11,3,0,9,0,1,26,0,5,20,0,11,0,3,27,16,0,0,0,10,0,16,0,12,0,6,27,27,16,0,2,0,13,0,14,0,15,11,3,0,8,0,3,26,16,0,7,0,8,0,4,26,26,16,17,7},
{runtime[0],runtime[2],runtime[18],runtime[22],runtime[24],runtime[28],runtime[31],runtime[45],runtime[46],runtime[50],runtime[55],runtime[56],runtime[60],1,5,9,2,3},
{{0,1,0}},
{{0,0}},
{{25,25,27,27,29,29,29,29,23,23,22,22,23,21,21,21,19,19,18,18,19,18,17,17,16,16,15,15,14,14,13,13,14,16,13,12,12,6,6,8,8,10,10,10,10,5,5,4,4,5,4,3,3,2,2,1,1,2,3,1,12,0},{25,25,27,27,29,29,29,29,23,23,22,22,23,21,21,21,19,19,18,18,19,24,17,17,16,16,15,15,14,14,13,13,14,16,17,12,12,6,6,8,8,10,10,10,10,5,5,4,4,5,5,3,3,2,2,1,1,2,3,3,12,11}},
std::make_shared<Array>(U"(≍˘˜⥊˘1‿5‿9)≡⌽⎉2⊸+⥊⟜(↕×´)3‿2‿1")
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
