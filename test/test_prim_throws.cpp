/*
 * This file is generated, don't edit!
 * Generated by the CXBQN build system on 2021-11-18T07:37:44
 */
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("'a'+'c'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'a'+'c'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[0], std::make_shared<Character>(U'a'),
                   std::make_shared<Character>(U'c')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{4, 4, 3, 3, 0, 0, 3, 0}, {6, 6, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\'a\'+\'c\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←-⋄f+2") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←-⋄f+2");
  CompileParams p{{0, 1, 33, 0, 0, 48, 6, 0, 2, 0, 0, 34, 0, 0, 17, 7},
                  {runtime[0], runtime[1], 2},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{2, 2, 0, 0, 0, 0, 1, 6, 6, 5, 5, 4, 4, 4, 5, 4},
                   {2, 2, 0, 0, 0, 0, 1, 6, 6, 5, 5, 4, 4, 4, 5, 4}},
                  std::make_shared<Array>(U"F←-⋄f+2")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("97-'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "97-'a'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[1], 97, std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{3, 3, 2, 2, 0, 0, 2, 0}, {5, 5, 2, 2, 1, 1, 2, 1}},
                  std::make_shared<Array>(U"97-\'a\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("@-1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "@-1");
  CompileParams p{{0, 1, 0, 0, 0, 2, 17, 7},
                  {runtime[1], 1, std::make_shared<Character>(U'\0')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{2, 2, 1, 1, 0, 0, 1, 0}, {2, 2, 1, 1, 0, 0, 1, 0}},
                  std::make_shared<Array>(U"@-1")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("-'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "-'a'");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[1], std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {3, 3, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"-\'a\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←÷⋄-f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←÷⋄-f");
  CompileParams p{{0, 1, 33, 0, 0, 48, 6, 34, 0, 0, 0, 0, 16, 7},
                  {runtime[1], runtime[3]},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{2, 2, 0, 0, 0, 0, 1, 5, 5, 5, 4, 4, 4, 4},
                   {2, 2, 0, 0, 0, 0, 1, 5, 5, 5, 4, 4, 4, 4}},
                  std::make_shared<Array>(U"F←÷⋄-f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("2×'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "2×'a'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[2], 2, std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{2, 2, 1, 1, 0, 0, 1, 0}, {4, 4, 1, 1, 0, 0, 1, 0}},
                  std::make_shared<Array>(U"2×\'a\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("÷'b'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "÷'b'");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[3], std::make_shared<Character>(U'b')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {3, 3, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"÷\'b\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←√-⋄÷f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←√-⋄÷f");
  CompileParams p{{0, 0, 0, 2, 20, 33, 0, 0, 48, 6, 34, 0, 0, 0, 1, 16, 7},
                  {runtime[1], runtime[3], runtime[5]},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{3, 3, 2, 2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 5, 5},
                   {3, 3, 2, 2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 5, 5}},
                  std::make_shared<Array>(U"F←√-⋄÷f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("⋆'π'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⋆'π'");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[4], std::make_shared<Character>(U'π')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {3, 3, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"⋆\'π\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("'e'⋆'π'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'e'⋆'π'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[4], std::make_shared<Character>(U'e'),
                   std::make_shared<Character>(U'π')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{4, 4, 3, 3, 0, 0, 3, 0}, {6, 6, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\'e\'⋆\'π\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←⌈⋄⌊f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←⌈⋄⌊f");
  CompileParams p{{0, 1, 33, 0, 0, 48, 6, 34, 0, 0, 0, 0, 16, 7},
                  {runtime[6], runtime[7]},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{2, 2, 0, 0, 0, 0, 1, 5, 5, 5, 4, 4, 4, 4},
                   {2, 2, 0, 0, 0, 0, 1, 5, 5, 5, 4, 4, 4, 4}},
                  std::make_shared<Array>(U"F←⌈⋄⌊f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←+⋄G←-⋄f≤g") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←+⋄G←-⋄f≤g");
  CompileParams p{{0,  0, 33, 0, 0, 48, 6, 0,  1, 33, 0,  1,
                   48, 6, 34, 0, 1, 0,  2, 34, 0, 0,  17, 7},
                  {runtime[0], runtime[1], runtime[16]},
                  {{0, 1, 0}},
                  {{0, 2}},
                  {{2, 2, 0,  0,  0,  0, 1, 6, 6, 4, 4, 4,
                    4, 5, 10, 10, 10, 9, 9, 8, 8, 8, 9, 8},
                   {2, 2, 0,  0,  0,  0, 1, 6, 6, 4, 4, 4,
                    4, 5, 10, 10, 10, 9, 9, 8, 8, 8, 9, 8}},
                  std::make_shared<Array>(U"F←+⋄G←-⋄f≤g")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("!0") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "!0");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[43], 0},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"!0")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("\"error\"!\"abc\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"error\"!\"abc\"");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[43], std::make_shared<Array>(U"error"),
                   std::make_shared<Array>(U"abc")},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{8, 8, 7, 7, 0, 0, 7, 0}, {12, 12, 7, 7, 6, 6, 7, 6}},
                  std::make_shared<Array>(U"\"error\"!\"abc\"")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("√'x'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "√'x'");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[5], std::make_shared<Character>(U'x')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {3, 3, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"√\'x\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("'a'∧¯1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'a'∧¯1");
  CompileParams p{{0, 1, 0, 0, 0, 2, 17, 7},
                  {runtime[10], -1, std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{4, 4, 3, 3, 0, 0, 3, 0}, {5, 5, 3, 3, 2, 2, 3, 2}},
                  std::make_shared<Array>(U"\'a\'∧¯1")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←-⋄2∨f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←-⋄2∨f");
  CompileParams p{{0, 0, 33, 0, 0, 48, 6, 34, 0, 0, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[11], 2},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 4, 4, 5, 4},
                   {2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 4, 4, 5, 4}},
                  std::make_shared<Array>(U"F←-⋄2∨f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("¬'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¬'a'");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[9], std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {3, 3, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"¬\'a\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("2¬'c'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "2¬'c'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[9], 2, std::make_shared<Character>(U'c')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{2, 2, 1, 1, 0, 0, 1, 0}, {4, 4, 1, 1, 0, 0, 1, 0}},
                  std::make_shared<Array>(U"2¬\'c\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←{𝕩}⋄0¬f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←{𝕩}⋄0¬f");
  CompileParams p{
      {1, 1, 33, 0, 0, 48, 6, 34, 0, 0, 0, 0, 0, 1, 17, 7, 34, 0, 1, 7},
      {runtime[9], 0},
      {{0, 1, 0}, {0, 0, 1}},
      {{0, 1}, {16, 3}},
      {{2, 2, 0, 0, 0, 0, 1, 8, 8, 8, 7, 7, 6, 6, 7, 2, 3, 3, 3, 3},
       {4, 4, 0, 0, 0, 0, 1, 8, 8, 8, 7, 7, 6, 6, 7, 4, 3, 3, 3, 3}},
      std::make_shared<Array>(U"F←{𝕩}⋄0¬f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←+-⋄|f") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "F←+-⋄|f");
  CompileParams p{{0, 1, 0, 0, 20, 33, 0, 0, 48, 6, 34, 0, 0, 0, 2, 16, 7},
                  {runtime[0], runtime[1], runtime[8]},
                  {{0, 1, 0}},
                  {{0, 1}},
                  {{3, 3, 2, 2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 5, 5},
                   {3, 3, 2, 2, 2, 0, 0, 0, 0, 1, 6, 6, 6, 5, 5, 5, 5}},
                  std::make_shared<Array>(U"F←+-⋄|f")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("26|'A'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "26|'A'");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[8], 26, std::make_shared<Character>(U'A')},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{3, 3, 2, 2, 0, 0, 2, 0}, {5, 5, 2, 2, 1, 1, 2, 1}},
                  std::make_shared<Array>(U"26|\'A\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("⊑\"\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⊑\"\"");
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[37], std::make_shared<Array>(U"")},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{1, 1, 0, 0, 0, 0}, {2, 2, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"⊑\"\"")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("⊑2‿0⥊⟨⟩") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⊑2‿0⥊⟨⟩");
  CompileParams p{{11, 0, 0, 0, 0, 2, 0, 3, 11, 2, 17, 0, 1, 16, 7},
                  {runtime[22], runtime[37], 2, 0},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{5, 5, 4, 4, 1, 1, 3, 3, 3, 3, 4, 0, 0, 0, 0},
                   {6, 6, 4, 4, 1, 1, 3, 3, 3, 3, 4, 0, 0, 0, 0}},
                  std::make_shared<Array>(U"⊑2‿0⥊⟨⟩")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("+´11") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "+´11");
  CompileParams p{{0, 2, 0, 1, 0, 0, 26, 16, 7},
                  {runtime[0], runtime[50], 11},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{2, 2, 1, 1, 0, 0, 1, 0, 0}, {3, 3, 1, 1, 0, 0, 1, 1, 0}},
                  std::make_shared<Array>(U"+´11")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("-´<'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "-´<'a'");
  CompileParams p{
      {0, 3, 0, 1, 16, 0, 2, 0, 0, 26, 16, 7},
      {runtime[1], runtime[12], runtime[50], std::make_shared<Character>(U'a')},
      {{0, 1, 0}},
      {{0, 0}},
      {{3, 3, 2, 2, 2, 1, 1, 0, 0, 1, 0, 0},
       {5, 5, 2, 2, 2, 1, 1, 0, 0, 1, 1, 0}},
      std::make_shared<Array>(U"-´<\'a\'")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("×´3‿1⥊\"abc\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "×´3‿1⥊\"abc\"");
  CompileParams p{{0, 5, 0, 1, 0, 3, 0, 4, 11, 2, 17, 0, 2, 0, 0, 26, 16, 7},
                  {runtime[2], runtime[22], runtime[50], 3, 1,
                   std::make_shared<Array>(U"abc")},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{6, 6, 5, 5, 2, 2, 4, 4, 4, 4, 5, 1, 1, 0, 0, 1, 0, 0},
                   {10, 10, 5, 5, 2, 2, 4, 4, 4, 4, 5, 1, 1, 0, 0, 1, 1, 0}},
                  std::make_shared<Array>(U"×´3‿1⥊\"abc\"")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("2‿3⊢¨4‿5‿6") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "2‿3⊢¨4‿5‿6");
  CompileParams p{
      {0, 4, 0, 5, 0, 6, 11, 3, 0, 1, 0, 0, 26, 0, 2, 0, 3, 11, 2, 17, 7},
      {runtime[21], runtime[47], 2, 3, 4, 5, 6},
      {{0, 1, 0}},
      {{0, 0}},
      {{5, 5, 7, 7, 9, 9, 9, 9, 4, 4, 3, 3, 4, 0, 0, 2, 2, 2, 2, 3, 2},
       {5, 5, 7, 7, 9, 9, 9, 9, 4, 4, 3, 3, 4, 0, 0, 2, 2, 2, 2, 4, 2}},
      std::make_shared<Array>(U"2‿3⊢¨4‿5‿6")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("\"abcd\"-\"a\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"abcd\"-\"a\"");
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[1], std::make_shared<Array>(U"abcd"),
                   std::make_shared<Array>(U"a")},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{7, 7, 6, 6, 0, 0, 6, 0}, {9, 9, 6, 6, 5, 5, 6, 5}},
                  std::make_shared<Array>(U"\"abcd\"-\"a\"")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("(↕4)×(↕3)⊢⌜↕2") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "(↕4)×(↕3)⊢⌜↕2");
  CompileParams p{{0, 6,  0,  2, 16, 0, 3, 0, 1, 26, 0,  5, 0,
                   2, 16, 17, 0, 0,  0, 4, 0, 2, 16, 17, 7},
                  {runtime[2], runtime[21], runtime[28], runtime[48], 4, 3, 2},
                  {{0, 1, 0}},
                  {{0, 0}},
                  {{12, 12, 11, 11, 11, 10, 10, 9, 9, 10, 7, 7, 6,
                    6,  6,  9,  4,  4,  2,  2,  1, 1, 1,  4, 0},
                   {12, 12, 11, 11, 11, 10, 10, 9, 9, 10, 7, 7, 6,
                    6,  6,  10, 4,  4,  2,  2,  1, 1, 1,  4, 3}},
                  std::make_shared<Array>(U"(↕4)×(↕3)⊢⌜↕2")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("10⊑↕10") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "10⊑↕10");
  CompileParams p{
      {0, 2, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[28], runtime[37], 10},
      {{0, 1, 0}},
      {{0, 0}},
      {{4, 4, 3, 3, 3, 2, 2, 0, 0, 2, 0}, {5, 5, 3, 3, 3, 2, 2, 1, 1, 2, 1}},
      std::make_shared<Array>(U"10⊑↕10")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("¯11⊑↕10") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯11⊑↕10");
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[28], runtime[37], -11, 10},
      {{0, 1, 0}},
      {{0, 0}},
      {{5, 5, 4, 4, 4, 3, 3, 0, 0, 3, 0}, {6, 6, 4, 4, 4, 3, 3, 2, 2, 3, 2}},
      std::make_shared<Array>(U"¯11⊑↕10")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("0.5⊑↕10") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0.5⊑↕10");
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[28], runtime[37], 0.5, 10},
      {{0, 1, 0}},
      {{0, 0}},
      {{5, 5, 4, 4, 4, 3, 3, 0, 0, 3, 0}, {6, 6, 4, 4, 4, 3, 3, 2, 2, 3, 2}},
      std::make_shared<Array>(U"0.5⊑↕10")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("'x'⊑↕10") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'x'⊑↕10");
  CompileParams p{
      {0, 2, 0, 0, 16, 0, 1, 0, 3, 17, 7},
      {runtime[28], runtime[37], 10, std::make_shared<Character>(U'x')},
      {{0, 1, 0}},
      {{0, 0}},
      {{5, 5, 4, 4, 4, 3, 3, 0, 0, 3, 0}, {6, 6, 4, 4, 4, 3, 3, 2, 2, 3, 2}},
      std::make_shared<Array>(U"\'x\'⊑↕10")};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}
