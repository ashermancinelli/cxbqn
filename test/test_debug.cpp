#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

//TEST_CASE("'a'≡⟨⟩⊑'a'") {
//  const auto rt = provides::get_runtime_setprims_cached_annot();
//  const auto runtime = rt->values;
//  spdlog::critical("test='{}'", "'a'≡⟨⟩⊑'a'");
//  CompileParams p({0, 2, 0, 1, 11, 0, 17, 0, 0, 0, 2, 17, 7},
//                  {runtime[18], runtime[37], std::make_shared<Character>(U'a')},
//                  {{0, 1, 0}}, {{0, 0}},
//                  {{7, 7, 6, 6, 4, 4, 6, 3, 3, 0, 0, 3, 0},
//                   {9, 9, 6, 6, 5, 5, 6, 3, 3, 2, 2, 3, 2}},
//                  std::make_shared<Array>(U"\'a\'≡⟨⟩⊑\'a\'"));
//  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
//                     p.source_indices.value(), p.source_str);
//  REQUIRE(nullptr != ret.v);
//  REQUIRE(nullptr != ret.scp);
//  auto n = dynamic_pointer_cast<Number>(ret.v);
//  REQUIRE(nullptr != n);
//  CHECK(1 == doctest::Approx(n->v));
//}

TEST_CASE("Check PrimInd") {
  spdlog::critical("test primind");
  const auto runtime = provides::get_runtime_setprims_annot()->values;
  CompileParams p(
      {0, 12, 0, 5, 16, 0,  0,  0, 7,  17, 0, 3,  0,  9, 0,  1,  11, 2,  17,
       0, 3,  0, 4, 0,  12, 11, 2, 17, 0,  3, 0,  11, 0, 6,  11, 2,  17, 0,
       3, 16, 0, 2, 0,  7,  0,  8, 0,  9,  0, 10, 0,  7, 11, 5,  17, 7},
      {runtime[0], runtime[6], runtime[18], runtime[22], runtime[26],
       runtime[28], runtime[31], 1, 2, 3, 0, 5, 4},
      {{0, 1, 0}}, {{0, 0}},
      {{26, 26, 25, 25, 25, 24, 24, 23, 23, 24, 22, 22, 19, 19,
        21, 21, 21, 21, 22, 18, 18, 15, 15, 17, 17, 17, 17, 18,
        14, 14, 11, 11, 13, 13, 13, 13, 14, 10, 10, 10, 9,  9,
        0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,  8},
       {26, 26, 25, 25, 25, 24, 24, 23, 23, 24, 22, 22, 19, 19,
        21, 21, 21, 21, 22, 18, 18, 15, 15, 17, 17, 17, 17, 18,
        14, 14, 11, 11, 13, 13, 13, 13, 14, 10, 10, 10, 9,  9,
        0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,  8}},
      std::make_shared<Array>(U"1‿2‿3‿0‿1≡⥊5‿⌽⥊↑‿4⥊3‿⌊⥊1+↕4")

  );
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  REQUIRE(4 == doctest::Approx(n->v));
}
