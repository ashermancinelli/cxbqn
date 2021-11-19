/*
 * This file is generated, don't edit!
 * Generated by the CXBQN build system on 2021-11-18T17:59:03
 */
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("⟨⟩≡⟨⟩∾\"\"") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨⟩≡⟨⟩∾\"\"");
  CompileParams p({0, 2, 0, 1, 11, 0, 17, 0, 0, 11, 0, 17, 7},
                  {runtime[18], runtime[23], std::make_shared<Array>(U"")},
                  {{0, 1, 0}}, {{0, 0}},
                  {{6, 6, 5, 5, 3, 3, 5, 2, 2, 0, 0, 2, 0},
                   {7, 7, 5, 5, 4, 4, 5, 2, 2, 1, 1, 2, 1}},
                  std::make_shared<Array>(U"⟨⟩≡⟨⟩∾\"\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("\"a\"≡⟨⟩∾\"a\"") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"a\"≡⟨⟩∾\"a\"");
  CompileParams p({0, 2, 0, 1, 11, 0, 17, 0, 0, 0, 2, 17, 7},
                  {runtime[18], runtime[23], std::make_shared<Array>(U"a")},
                  {{0, 1, 0}}, {{0, 0}},
                  {{7, 7, 6, 6, 4, 4, 6, 3, 3, 0, 0, 3, 0},
                   {9, 9, 6, 6, 5, 5, 6, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\"a\"≡⟨⟩∾\"a\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("\"a\"≡\"a\"∾⟨⟩") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"a\"≡\"a\"∾⟨⟩");
  CompileParams p({11, 0, 0, 1, 0, 2, 17, 0, 0, 0, 2, 17, 7},
                  {runtime[18], runtime[23], std::make_shared<Array>(U"a")},
                  {{0, 1, 0}}, {{0, 0}},
                  {{8, 8, 7, 7, 4, 4, 7, 3, 3, 0, 0, 3, 0},
                   {9, 9, 7, 7, 6, 6, 7, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\"a\"≡\"a\"∾⟨⟩"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("\"aBCD\"≡\"a\"∾\"BCD\"") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"aBCD\"≡\"a\"∾\"BCD\"");
  CompileParams p({0, 4, 0, 1, 0, 3, 17, 0, 0, 0, 2, 17, 7},
                  {runtime[18], runtime[23], std::make_shared<Array>(U"aBCD"),
                   std::make_shared<Array>(U"a"),
                   std::make_shared<Array>(U"BCD")},
                  {{0, 1, 0}}, {{0, 0}},
                  {{11, 11, 10, 10, 7, 7, 10, 6, 6, 0, 0, 6, 0},
                   {15, 15, 10, 10, 9, 9, 10, 6, 6, 5, 5, 6, 5}},
                  std::make_shared<Array>(U"\"aBCD\"≡\"a\"∾\"BCD\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("((+⌜˜≠¨)≡(≠¨∾⌜˜))\"\"‿⟨2,3⟩‿\"abcde\"") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "((+⌜˜≠¨)≡(≠¨∾⌜˜))\"\"‿⟨2,3⟩‿\"abcde\"");
  CompileParams p(
      {0, 9, 0,  7,  0,  8, 11, 2, 0, 10, 11, 3,  0,  4,  0,
       6, 0, 3,  26, 26, 0, 5,  0, 1, 26, 20, 0,  2,  0,  5,
       0, 1, 26, 0,  4,  0, 6,  0, 0, 26, 26, 20, 21, 16, 7},
      {runtime[0], runtime[14], runtime[18], runtime[23], runtime[45],
       runtime[47], runtime[48], 2, 3, std::make_shared<Array>(U""),
       std::make_shared<Array>(U"abcde")},
      {{0, 1, 0}}, {{0, 0}},
      {{17, 17, 21, 21, 23, 23, 20, 20, 26, 26, 26, 26, 14, 14, 13,
        13, 12, 12, 13, 14, 11, 11, 10, 10, 11, 10, 8,  8,  6,  6,
        5,  5,  6,  4,  4,  3,  3,  2,  2,  3,  4,  2,  8,  0,  0},
       {18, 18, 21, 21, 23, 23, 24, 24, 32, 32, 32, 32, 14, 14, 13,
        13, 12, 12, 13, 14, 11, 11, 10, 10, 11, 11, 8,  8,  6,  6,
        5,  5,  6,  4,  4,  3,  3,  2,  2,  3,  4,  4,  8,  16, 16}},
      std::make_shared<Array>(U"((+⌜˜≠¨)≡(≠¨∾⌜˜))\"\"‿⟨2,3⟩‿\"abcde\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)3‿4") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)3‿4");
  CompileParams p(
      {0,  11, 0, 10, 11, 2, 0,  6, 0, 4,  0,  7,  0,  5,  0, 0,
       26, 0,  8, 0,  10, 0, 9,  0, 1, 27, 27, 27, 26, 0,  2, 0,
       6,  0,  1, 26, 0,  4, 20, 0, 9, 0,  3,  27, 21, 16, 7},
      {runtime[0], runtime[2], runtime[18], runtime[22], runtime[28],
       runtime[48], runtime[50], runtime[54], runtime[55], runtime[56], 4, 3},
      {{0, 1, 0}}, {{0, 0}},
      {{23, 23, 25, 25, 25, 25, 21, 21, 20, 20, 19, 19, 17, 17, 16, 16,
        17, 14, 14, 12, 12, 11, 11, 10, 10, 11, 14, 19, 21, 8,  8,  6,
        6,  5,  5,  6,  4,  4,  4,  2,  2,  1,  1,  2,  8,  0,  0},
       {23, 23, 25, 25, 25, 25, 21, 21, 20, 20, 19, 19, 17, 17, 16, 16,
        17, 14, 14, 12, 12, 11, 11, 10, 10, 11, 14, 19, 21, 8,  8,  6,
        6,  5,  5,  6,  4,  4,  4,  2,  2,  1,  1,  2,  8,  22, 22}},
      std::make_shared<Array>(U"(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)3‿4"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)0‿4") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)0‿4");
  CompileParams p(
      {0,  11, 0, 10, 11, 2, 0,  6, 0, 4,  0,  7,  0,  5,  0, 0,
       26, 0,  8, 0,  10, 0, 9,  0, 1, 27, 27, 27, 26, 0,  2, 0,
       6,  0,  1, 26, 0,  4, 20, 0, 9, 0,  3,  27, 21, 16, 7},
      {runtime[0], runtime[2], runtime[18], runtime[22], runtime[28],
       runtime[48], runtime[50], runtime[54], runtime[55], runtime[56], 4, 0},
      {{0, 1, 0}}, {{0, 0}},
      {{23, 23, 25, 25, 25, 25, 21, 21, 20, 20, 19, 19, 17, 17, 16, 16,
        17, 14, 14, 12, 12, 11, 11, 10, 10, 11, 14, 19, 21, 8,  8,  6,
        6,  5,  5,  6,  4,  4,  4,  2,  2,  1,  1,  2,  8,  0,  0},
       {23, 23, 25, 25, 25, 25, 21, 21, 20, 20, 19, 19, 17, 17, 16, 16,
        17, 14, 14, 12, 12, 11, 11, 10, 10, 11, 14, 19, 21, 8,  8,  6,
        6,  5,  5,  6,  4,  4,  4,  2,  2,  1,  1,  2,  8,  22, 22}},
      std::make_shared<Array>(U"(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)0‿4"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(3‿2‿0⥊\"\")≡(3‿2⥊↕6)+⌜\"\"") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(3‿2‿0⥊\"\")≡(3‿2⥊↕6)+⌜\"\"");
  CompileParams p({0, 9, 0, 4, 0, 0,  26, 0,  8,  0, 3,  16, 0,
                   2, 0, 5, 0, 6, 11, 2,  17, 17, 0, 1,  0,  9,
                   0, 2, 0, 5, 0, 6,  0,  7,  11, 3, 17, 17, 7},
                  {runtime[0], runtime[18], runtime[22], runtime[28],
                   runtime[48], 3, 2, 0, 6, std::make_shared<Array>(U"")},
                  {{0, 1, 0}}, {{0, 0}},
                  {{21, 21, 20, 20, 19, 19, 20, 17, 17, 16, 16, 16, 15,
                    15, 12, 12, 14, 14, 14, 14, 15, 19, 10, 10, 7,  7,
                    6,  6,  1,  1,  3,  3,  5,  5,  5,  5,  6,  10, 0},
                   {22, 22, 20, 20, 19, 19, 20, 17, 17, 16, 16, 16, 15,
                    15, 12, 12, 14, 14, 14, 14, 15, 20, 10, 10, 8,  8,
                    6,  6,  1,  1,  3,  3,  5,  5,  5,  5,  6,  10, 9}},
                  std::make_shared<Array>(U"(3‿2‿0⥊\"\")≡(3‿2⥊↕6)+⌜\"\""));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<-2)≡-¨2") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(<-2)≡-¨2");
  CompileParams p(
      {0, 4, 0, 3, 0, 0, 26, 16, 0, 2, 0, 4, 0, 0, 16, 0, 1, 16, 17, 7},
      {runtime[1], runtime[12], runtime[18], runtime[47], 2}, {{0, 1, 0}},
      {{0, 0}},
      {{8, 8, 7, 7, 6, 6, 7, 6, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 0},
       {8, 8, 7, 7, 6, 6, 7, 7, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 4}},
      std::make_shared<Array>(U"(<-2)≡-¨2"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<<2)≡<¨2") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(<<2)≡<¨2");
  CompileParams p(
      {0, 3, 0, 2, 0, 0, 26, 16, 0, 1, 0, 3, 0, 0, 16, 0, 0, 16, 17, 7},
      {runtime[12], runtime[18], runtime[47], 2}, {{0, 1, 0}}, {{0, 0}},
      {{8, 8, 7, 7, 6, 6, 7, 6, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 0},
       {8, 8, 7, 7, 6, 6, 7, 7, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 4}},
      std::make_shared<Array>(U"(<<2)≡<¨2"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE(
    "⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical(
      "test='{}'",
      "⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩");
  CompileParams p(
      {0,  4, 0, 0,  16, 0,  5,  0, 0, 16, 0, 6,  0,  0,  16, 0,  4,  0, 7,  0,
       6,  0, 7, 11, 4,  0,  2,  0, 6, 0,  6, 11, 2,  17, 0,  3,  0,  0, 26, 16,
       11, 3, 0, 8,  0,  0,  16, 0, 9, 0,  0, 16, 11, 2,  11, 3,  0,  0, 16, 0,
       1,  0, 4, 0,  5,  0,  6,  0, 4, 0,  7, 0,  6,  0,  7,  11, 4,  0, 2,  0,
       6,  0, 6, 11, 2,  17, 11, 3, 0, 8,  0, 9,  11, 2,  11, 3,  17, 7},
      {runtime[1], runtime[18], runtime[22], runtime[47], 1, 3, 2, 0, 5, 4},
      {{0, 1, 0}}, {{0, 0}},
      {{33, 33, 32, 32, 32, 37, 37, 36, 36, 36, 40, 40, 39, 39, 39, 49, 49,
        51, 51, 53, 53, 55, 55, 48, 48, 47, 47, 44, 44, 46, 46, 46, 46, 47,
        43, 43, 42, 42, 43, 42, 35, 35, 61, 61, 60, 60, 60, 64, 64, 63, 63,
        63, 59, 59, 31, 31, 30, 30, 30, 29, 29, 1,  1,  4,  4,  6,  6,  13,
        13, 15, 15, 17, 17, 19, 19, 12, 12, 11, 11, 8,  8,  10, 10, 10, 10,
        11, 3,  3,  24, 24, 26, 26, 23, 23, 0,  0,  29, 0},
       {33, 33, 32, 32, 32, 37, 37, 36, 36, 36, 40, 40, 39, 39, 39, 49, 49,
        51, 51, 53, 53, 55, 55, 56, 56, 47, 47, 44, 44, 46, 46, 46, 46, 47,
        43, 43, 42, 42, 43, 43, 57, 57, 61, 61, 60, 60, 60, 64, 64, 63, 63,
        63, 65, 65, 66, 66, 30, 30, 30, 29, 29, 1,  1,  4,  4,  6,  6,  13,
        13, 15, 15, 17, 17, 19, 19, 20, 20, 11, 11, 8,  8,  10, 10, 10, 10,
        11, 21, 21, 24, 24, 26, 26, 27, 27, 28, 28, 29, 28}},
      std::make_shared<Array>(U"⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-"
                              U"¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("3(+¨≡+⌜)↕6") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "3(+¨≡+⌜)↕6");
  CompileParams p(
      {0, 6, 0, 2, 16, 0, 4, 0, 0, 26, 0, 1, 0, 3, 0, 0, 26, 21, 0, 5, 17, 7},
      {runtime[0], runtime[18], runtime[28], runtime[47], runtime[48], 3, 6},
      {{0, 1, 0}}, {{0, 0}},
      {{9, 9, 8, 8, 8, 6, 6, 5, 5, 6, 4, 4, 3, 3, 2, 2, 3, 4, 0, 0, 1, 0},
       {9, 9, 8, 8, 8, 6, 6, 5, 5, 6, 4, 4, 3, 3, 2, 2, 3, 4, 0, 0, 7, 0}},
      std::make_shared<Array>(U"3(+¨≡+⌜)↕6"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("3‿4‿5‿6‿6≡{𝕊⍟(×≡)⊸∾⟜⥊´𝕩}⟨2,1⟩+⟨⟨⟨⟨1,2⟩,3⟩,4⟩,5⟩") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'",
                   "3‿4‿5‿6‿6≡{𝕊⍟(×≡)⊸∾⟜⥊´𝕩}⟨2,1⟩+⟨⟨⟨⟨1,2⟩,3⟩,4⟩,5⟩");
  CompileParams p(
      {0, 14, 0,  13, 11, 2,  0,  9,  11, 2,  0,  10, 11, 2,  0,  11, 11, 2, 0,
       0, 0,  13, 0,  14, 11, 2,  17, 1,  1,  16, 0,  2,  0,  9,  0,  10, 0, 11,
       0, 12, 0,  12, 11, 5,  17, 7,  34, 0,  1,  0,  5,  0,  3,  0,  7,  0, 4,
       0, 6,  0,  2,  0,  1,  20, 0,  8,  34, 0,  0,  27, 27, 27, 26, 16, 7},
      {runtime[0], runtime[2], runtime[18], runtime[22], runtime[23],
       runtime[50], runtime[55], runtime[56], runtime[62], 3, 4, 5, 6, 2, 1},
      {{0, 1, 0}, {0, 0, 1}}, {{0, 0}, {46, 3}},
      {{34, 34, 36, 36, 33, 33, 39, 39, 32, 32, 42, 42, 31, 31, 45,
        45, 30, 30, 29, 29, 25, 25, 27, 27, 24, 24, 29, 10, 10, 10,
        9,  9,  0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,
        10, 22, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18, 17, 17, 15,
        15, 14, 14, 14, 12, 12, 11, 11, 11, 12, 17, 19, 21, 11, 11},
       {34, 34, 36, 36, 37, 37, 39, 39, 40, 40, 42, 42, 43, 43, 45,
        45, 46, 46, 29, 29, 25, 25, 27, 27, 28, 28, 29, 23, 23, 23,
        9,  9,  0,  0,  2,  2,  4,  4,  6,  6,  8,  8,  8,  8,  9,
        23, 22, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18, 17, 17, 15,
        15, 14, 14, 14, 12, 12, 11, 11, 11, 12, 17, 19, 21, 21, 11}},
      std::make_shared<Array>(
          U"3‿4‿5‿6‿6≡{𝕊⍟(×≡)⊸∾⟜⥊´𝕩}⟨2,1⟩+⟨⟨⟨⟨1,2⟩,3⟩,4⟩,5⟩"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("3‿2≡≢(↕3)(⊣×⊢⌜)↕2") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "3‿2≡≢(↕3)(⊣×⊢⌜)↕2");
  CompileParams p(
      {0, 8, 0,  5,  16, 0, 6,  0, 4, 26, 0, 0, 0, 3,  21, 0,  7,
       0, 5, 16, 17, 0,  2, 16, 0, 1, 0,  7, 0, 8, 11, 2,  17, 7},
      {runtime[2], runtime[18], runtime[19], runtime[20], runtime[21],
       runtime[28], runtime[48], 3, 2},
      {{0, 1, 0}}, {{0, 0}},
      {{16, 16, 15, 15, 15, 13, 13, 12, 12, 13, 11, 11, 10, 10, 11, 7, 7,
        6,  6,  6,  9,  4,  4,  4,  3,  3,  0,  0,  2,  2,  2,  2,  3, 2},
       {16, 16, 15, 15, 15, 13, 13, 12, 12, 13, 11, 11, 10, 10, 11, 7, 7,
        6,  6,  6,  14, 4,  4,  4,  3,  3,  0,  0,  2,  2,  2,  2,  3, 2}},
      std::make_shared<Array>(U"3‿2≡≢(↕3)(⊣×⊢⌜)↕2"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<-4)≡-<4") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(<-4)≡-<4");
  CompileParams p(
      {0, 3, 0, 1, 16, 0, 0, 16, 0, 2, 0, 3, 0, 0, 16, 0, 1, 16, 17, 7},
      {runtime[1], runtime[12], runtime[18], 4}, {{0, 1, 0}}, {{0, 0}},
      {{8, 8, 7, 7, 7, 6, 6, 6, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 0},
       {8, 8, 7, 7, 7, 6, 6, 6, 5, 5, 3, 3, 2, 2, 2, 1, 1, 1, 5, 4}},
      std::make_shared<Array>(U"(<-4)≡-<4"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<2)≡1+<1") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(<2)≡1+<1");
  CompileParams p({0, 4, 0, 1, 16, 0, 0, 0, 4, 17, 0, 2, 0, 3, 0, 1, 16, 17, 7},
                  {runtime[0], runtime[12], runtime[18], 2, 1}, {{0, 1, 0}},
                  {{0, 0}},
                  {{8, 8, 7, 7, 7, 6, 6, 5, 5, 6, 4, 4, 2, 2, 1, 1, 1, 4, 0},
                   {8, 8, 7, 7, 7, 6, 6, 5, 5, 6, 4, 4, 2, 2, 1, 1, 1, 4, 3}},
                  std::make_shared<Array>(U"(<2)≡1+<1"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(=¨⟜(⥊⟜(↕×´)3‿4)≡(↕4)=⌜˜4|⊢)1‿6‿8") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(=¨⟜(⥊⟜(↕×´)3‿4)≡(↕4)=⌜˜4|⊢)1‿6‿8");
  CompileParams p(
      {0,  14, 0,  15, 0,  16, 11, 3, 0,  4,  0,  1,  0,  13, 21, 0,
       7,  0,  9,  0,  2,  26, 26, 0, 13, 0,  6,  16, 21, 0,  3,  0,
       12, 0,  13, 11, 2,  0,  10, 0, 0,  26, 0,  6,  20, 0,  11, 0,
       5,  27, 16, 0,  11, 0,  8,  0, 2,  26, 27, 21, 16, 7},
      {runtime[2], runtime[8], runtime[15], runtime[18], runtime[21],
       runtime[22], runtime[28], runtime[45], runtime[47], runtime[48],
       runtime[50], runtime[56], 3, 4, 1, 6, 8},
      {{0, 1, 0}}, {{0, 0}},
      {{28, 28, 30, 30, 32, 32, 32, 32, 26, 26, 25, 25, 24, 24, 25, 23,
        23, 22, 22, 21, 21, 22, 23, 19, 19, 18, 18, 18, 21, 16, 16, 12,
        12, 14, 14, 14, 14, 10, 10, 9,  9,  10, 8,  8,  8,  6,  6,  5,
        5,  6,  5,  3,  3,  2,  2,  1,  1,  2,  3,  16, 0,  0},
       {28, 28, 30, 30, 32, 32, 32, 32, 26, 26, 25, 25, 24, 24, 25, 23,
        23, 22, 22, 21, 21, 22, 23, 19, 19, 18, 18, 18, 23, 16, 16, 12,
        12, 14, 14, 14, 14, 10, 10, 9,  9,  10, 8,  8,  8,  6,  6,  5,
        5,  6,  11, 3,  3,  2,  2,  1,  1,  2,  3,  16, 27, 27}},
      std::make_shared<Array>(U"(=¨⟜(⥊⟜(↕×´)3‿4)≡(↕4)=⌜˜4|⊢)1‿6‿8"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0‿1≡+‿-=⊑⟨-⟩") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0‿1≡+‿-=⊑⟨-⟩");
  CompileParams p(
      {0,  1, 11, 1, 0, 4, 16, 0, 2, 0,  0, 0,  1,
       11, 2, 17, 0, 3, 0, 5,  0, 6, 11, 2, 17, 7},
      {runtime[0], runtime[1], runtime[15], runtime[18], runtime[37], 0, 1},
      {{0, 1, 0}}, {{0, 0}},
      {{10, 10, 9, 9, 8, 8, 8, 7, 7, 4, 4, 6, 6,
        6,  6,  7, 3, 3, 0, 0, 2, 2, 2, 2, 3, 2},
       {10, 10, 11, 11, 8, 8, 8, 7, 7, 4, 4, 6, 6,
        6,  6,  7,  3,  3, 0, 0, 2, 2, 2, 2, 3, 2}},
      std::make_shared<Array>(U"0‿1≡+‿-=⊑⟨-⟩"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
