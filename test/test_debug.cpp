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
  spdlog::critical("test='{}'", "'a'≡⟨⟩⊑'a'");
  CompileParams p({0, 2, 0, 1, 11, 0, 17, 0, 0, 0, 2, 17, 7},
                  {runtime[18], runtime[37], std::make_shared<Character>(U'a')},
                  {{0, 1, 0}}, {{0, 0}},
                  {{7, 7, 6, 6, 4, 4, 6, 3, 3, 0, 0, 3, 0},
                   {9, 9, 6, 6, 5, 5, 6, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\'a\'≡⟨⟩⊑\'a\'"));
  fmt::print("startingtest\n");
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

// TEST_CASE("Check PrimInd") {
//  spdlog::critical("test primind");
//  const auto runtime = provides::get_runtime_setprims_annot()->values;
//  CompileParams p(
//      {0, 12, 0, 5, 16, 0,  0,  0, 7,  17, 0, 3,  0,  9, 0,  1,  11, 2,  17,
//       0, 3,  0, 4, 0,  12, 11, 2, 17, 0,  3, 0,  11, 0, 6,  11, 2,  17, 0,
//       3, 16, 0, 2, 0,  7,  0,  8, 0,  9,  0, 10, 0,  7, 11, 5,  17, 7},
//      {runtime[0], runtime[6], runtime[18], runtime[22], runtime[26],
//       runtime[28], runtime[31], 1, 2, 3, 0, 5, 4},
//      {{0, 1, 0}}, {{0, 0}},
//      {{26, 26, 25, 25, 25, 24, 24, 23, 23, 24, 22, 22, 19, 19,
//        21, 21, 21, 21, 22, 18, 18, 15, 15, 17, 17, 17, 17, 18,
//        14, 14, 11, 11, 13, 13, 13, 13, 14, 10, 10, 10, 9,  9,
//        0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,  8},
//       {26, 26, 25, 25, 25, 24, 24, 23, 23, 24, 22, 22, 19, 19,
//        21, 21, 21, 21, 22, 18, 18, 15, 15, 17, 17, 17, 17, 18,
//        14, 14, 11, 11, 13, 13, 13, 13, 14, 10, 10, 10, 9,  9,
//        0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,  8}},
//      std::make_shared<Array>(U"1‿2‿3‿0‿1≡⥊5‿⌽⥊↑‿4⥊3‿⌊⥊1+↕4")
//
//  );
//  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
//                     p.source_indices.value(), p.source_str);
//  REQUIRE(nullptr != ret.v);
//  REQUIRE(nullptr != ret.scp);
//  auto n = dynamic_pointer_cast<Number>(ret.v);
//  REQUIRE(nullptr != n);
//  REQUIRE(1 == doctest::Approx(n->v));
//}

/*
TEST_CASE("Dzaima's Sanity Check Prg") {
  spdlog::critical("sanity check");
  const auto runtime = provides::get_runtime_setprims_annot()->values;
  CompileParams p(
      {0,  20, 0,  2,  16, 0,  1,  16, 0,  8,  16, 6,  0,  13, 0, 0,  0,
       18, 17, 0,  4,  0,  21, 17, 0,  2,  16, 0,  1,  16, 0,  8, 16, 6,
       0,  22, 0,  3,  0,  15, 0,  12, 11, 2,  17, 0,  10, 0,  7, 26, 0,
       14, 17, 0,  2,  16, 0,  1,  16, 0,  8,  16, 6,  0,  13, 0, 6,  16,
       0,  0,  0,  19, 17, 0,  2,  16, 0,  1,  16, 0,  8,  16, 6, 0,  16,
       0,  6,  16, 0,  11, 0,  0,  26, 0,  24, 17, 0,  3,  16, 0, 9,  0,
       4,  26, 0,  23, 17, 0,  2,  16, 0,  1,  16, 0,  8,  16, 6, 0,  17,
       0,  0,  0,  18, 17, 0,  4,  0,  27, 17, 0,  4,  0,  26, 0, 5,  0,
       14, 17, 17, 0,  4,  0,  25, 17, 0,  2,  16, 0,  1,  16, 0, 8,  16,
       6,  0,  28, 0,  2,  16, 0,  1,  16, 0,  8,  16, 7},
      {runtime[0],
       runtime[14],
       runtime[19],
       runtime[22],
       runtime[23],
       runtime[27],
       runtime[28],
       runtime[36],
       runtime[43],
       runtime[45],
       runtime[46],
       runtime[48],
       runtime[53],
       10,
       -1,
       11,
       26,
       9,
       std::make_shared<Character>(U'\0'),
       std::make_shared<Character>(U'0'),
       std::make_shared<Array>(U"+×"),
       std::make_shared<Array>(U"⋄,"),
       std::make_shared<Array>(U"𝕊𝕏𝕎𝔽𝔾𝕤𝕩𝕨𝕣𝕗𝕘"),
       std::make_shared<Array>(U"_"),
       std::make_shared<Array>(U"aA"),
       std::make_shared<Array>(U"•"),
       std::make_shared<Array>(U"𝕨"),
       std::make_shared<Array>(U" "),
       std::make_shared<Array>(U"#\'\"@")},
      {{0, 1, 0}}, {{0, 0}},
      {{5,   5,   3,   3,   3,   2,   2,   2,   0,   0,   0,   10,  24,  24,
        23,  23,  22,  22,  23,  21,  21,  17,  17,  21,  15,  15,  15,  14,
        14,  14,  12,  12,  12,  27,  43,  43,  42,  42,  38,  38,  41,  41,
        41,  41,  42,  37,  37,  36,  36,  37,  34,  34,  36,  32,  32,  32,
        31,  31,  31,  29,  29,  29,  57,  69,  69,  68,  68,  68,  67,  67,
        64,  64,  67,  62,  62,  62,  61,  61,  61,  59,  59,  59,  72,  92,
        92,  91,  91,  91,  90,  90,  89,  89,  90,  85,  85,  89,  84,  84,
        84,  83,  83,  82,  82,  83,  79,  79,  82,  77,  77,  77,  76,  76,
        76,  74,  74,  74,  95,  121, 121, 120, 120, 119, 119, 120, 118, 118,
        115, 115, 118, 114, 114, 110, 110, 109, 109, 107, 107, 109, 114, 105,
        105, 102, 102, 105, 100, 100, 100, 99,  99,  99,  97,  97,  97,  123,
        130, 130, 128, 128, 128, 127, 127, 127, 125, 125, 125, 125},
       {8,   8,   3,   3,   3,   2,   2,   2,   0,   0,   0,   10,  25,  25,
        23,  23,  22,  22,  23,  21,  21,  20,  20,  21,  15,  15,  15,  14,
        14,  14,  12,  12,  12,  27,  55,  55,  42,  42,  39,  39,  41,  41,
        41,  41,  42,  37,  37,  36,  36,  37,  35,  35,  37,  32,  32,  32,
        31,  31,  31,  29,  29,  29,  57,  70,  70,  68,  68,  68,  67,  67,
        66,  66,  67,  62,  62,  62,  61,  61,  61,  59,  59,  59,  72,  93,
        93,  91,  91,  91,  90,  90,  89,  89,  90,  88,  88,  90,  84,  84,
        84,  83,  83,  82,  82,  83,  81,  81,  83,  77,  77,  77,  76,  76,
        76,  74,  74,  74,  95,  121, 121, 120, 120, 119, 119, 120, 118, 118,
        117, 117, 118, 114, 114, 112, 112, 109, 109, 108, 108, 109, 114, 105,
        105, 104, 104, 105, 100, 100, 100, 99,  99,  99,  97,  97,  97,  123,
        136, 136, 128, 128, 128, 127, 127, 127, 125, 125, 125, 125}},
      std::make_shared<Array>(
          U"! ≠≢ \"+×\" ⋄ ! ≠≢ \"⋄,\"∾@+10 ⋄ ! ≠≢ ¯1⊏˘11‿∘⥊\"𝕊𝕏𝕎𝔽𝔾𝕤𝕩𝕨𝕣𝕗𝕘\" ⋄ ! "
          U"≠≢ \'0\'+↕10 ⋄ ! ≠≢ \"_\"∾˜⥊\"aA\"+⌜↕26 ⋄ ! ≠≢ \"•\"∾(¯1↓\"𝕨\")∾\" "
          U"\"∾@+9 ⋄ ! ≠≢ \"#\'\"\"@\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  REQUIRE(1 == doctest::Approx(n->v));
}
*/
