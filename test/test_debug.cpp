#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

//TEST_CASE("4≡2+⍟¯1 6") {
//  const auto rt = provides::get_runtime_setprims_cached_annot();
//  const auto runtime = rt->values;
//  spdlog::critical("test='{}'", "4≡2+⍟¯1 6");
//  CompileParams p(
//      {0,9,0,1,0,7,0,6,0,8,11,3,17,0,3,0,6,0,4,0,2,27,26,0,5,0,0,27,16,7},
//{runtime[18],runtime[22],runtime[43],runtime[52],runtime[53],runtime[56],0,3,2,std::make_shared<Array>(U"")},
//{{0,1,0}},
//{{0,0}},
//{{14,14,13,13,8,8,10,10,12,12,12,12,13,6,6,5,5,4,4,3,3,4,6,1,1,0,0,1,0,0},{15,15,13,13,8,8,10,10,12,12,12,12,13,6,6,5,5,4,4,3,3,4,6,1,1,0,0,1,7,0}},
//std::make_shared<Array>(U"≡⟜(!∘0`)3‿0‿2⥊\"\"")
//      );
//  fmt::print("startingtest\n");
//  spdlog::critical("startingtest");
//  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
//                     p.source_indices.value(), p.source_str);
//  REQUIRE(nullptr != ret.v);
//  REQUIRE(nullptr != ret.scp);
//  auto n = dynamic_pointer_cast<Number>(ret.v);
//  REQUIRE(nullptr != n);
//  CHECK(1 == doctest::Approx(n->v));
//}

TEST_CASE("empty ar") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "empty ar");
  CompileParams p(
      {11,0,0,2,0,0,26,16,0,1,11,0,17,7},
{runtime[2],runtime[18],runtime[52]},
{{0,1,0}},
{{0,0}},
{{5,5,4,4,3,3,4,3,2,2,0,0,2,0},{6,6,4,4,3,3,4,4,2,2,1,1,2,1}},
std::make_shared<Array>(U"⟨⟩≡×`⟨⟩")
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
