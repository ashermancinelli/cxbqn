#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;


//TEST_CASE("grade") {
//  const auto rt = provides::get_runtime_setprims_cached_annot();
//  const auto runtime = rt->values;
//  spdlog::critical("test='{}'", "grade");
//  CompileParams p(
//      {0,8,0,12,0,11,11,3,0,4,16,0,3,0,11,0,7,0,0,27,0,9,0,10,0,10,11,3,21,0,6,0,5,27,16,0,2,0,8,0,4,16,0,0,0,9,17,0,1,0,8,17,17,7},
//{runtime[0],runtime[6],runtime[18],runtime[21],runtime[28],runtime[38],runtime[56],runtime[61],5,3,0,1,2},
//{{0,1,0}},
//{{0,0}},
//{{23,23,25,25,27,27,27,27,22,22,22,20,20,19,19,18,18,17,17,18,12,12,14,14,16,16,16,16,17,10,10,9,9,10,9,8,8,6,6,5,5,5,4,4,3,3,4,2,2,1,1,2,8,0},{23,23,25,25,27,27,27,27,22,22,22,20,20,19,19,18,18,17,17,18,12,12,14,14,16,16,16,16,19,10,10,9,9,10,21,8,8,6,6,5,5,5,4,4,3,3,4,2,2,1,1,2,8,7}},
//std::make_shared<Array>(U"(5⌊3+↕5)≡⊐⟜(3‿0‿0+⚇1⊢)↕5‿2‿1")
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
TEST_CASE("grade") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0‿0‿1‿0‿2≡⊐\"ccacb\"");
  CompileParams p(
      {0,5,0,1,16,0,0,0,2,0,2,0,3,0,2,0,4,11,5,17,7},
{runtime[18],runtime[38],0,1,2,std::make_shared<Array>(U"ccacb")},
{{0,1,0}},
{{0,0}},
{{11,11,10,10,10,9,9,0,0,2,2,4,4,6,6,8,8,8,8,9,8},{17,17,10,10,10,9,9,0,0,2,2,4,4,6,6,8,8,8,8,9,8}},
std::make_shared<Array>(U"0‿0‿1‿0‿2≡⊐\"ccacb\"")
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
