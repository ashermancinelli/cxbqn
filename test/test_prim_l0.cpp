/*
 * This file is generated, don't edit!
 * Generated by the CXBQN build system on 2021-11-14T17:27:28
 */
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("0≡¯2+2") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡¯2+2");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[0], runtime[18], 0, -2, 2},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1e4≡5e3+5e3") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1e4≡5e3+5e3");
  CompileParams p{{0, 3, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[0], runtime[18], 10000, 5000},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("'c'≡'a'+2") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'c'≡'a'+2");
  CompileParams p{{0, 2, 0, 0, 0, 4, 17, 0, 1, 0, 3, 17, 7},
                  {runtime[0], runtime[18], 2,
                   std::make_shared<Character>(U'c'),
                   std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("'a'≡¯2+'c'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'a'≡¯2+'c'");
  CompileParams p{{0, 4, 0, 0, 0, 2, 17, 0, 1, 0, 3, 17, 7},
                  {runtime[0], runtime[18], -2,
                   std::make_shared<Character>(U'a'),
                   std::make_shared<Character>(U'c')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯∞≡1e6-∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯∞≡1e6-∞");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18],
                   std::make_shared<Number>(-1.0 / 0.0), 1000000,
                   std::make_shared<Number>(1.0 / 0.0)},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("4≡-¯4") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "4≡-¯4");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], 4, -4},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯∞≡-∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯∞≡-∞");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18],
                   std::make_shared<Number>(-1.0 / 0.0),
                   std::make_shared<Number>(1.0 / 0.0)},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("∞≡-¯∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "∞≡-¯∞");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], std::make_shared<Number>(1.0 / 0.0),
                   std::make_shared<Number>(-1.0 / 0.0)},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("4≡9-5") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "4≡9-5");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], 4, 9, 5},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("@≡'a'-97") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "@≡'a'-97");
  CompileParams p{{0, 2, 0, 0, 0, 4, 17, 0, 1, 0, 3, 17, 7},
                  {runtime[1], runtime[18], 97,
                   std::make_shared<Character>(U'\0'),
                   std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("3≡'d'-'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "3≡'d'-'a'");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], 3,
                   std::make_shared<Character>(U'd'),
                   std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("'Q'≡'q'+'A'-'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "'Q'≡'q'+'A'-'a'");
  CompileParams p{
      {0, 6, 0, 1, 0, 5, 17, 0, 0, 0, 4, 17, 0, 2, 0, 3, 17, 7},
      {runtime[0], runtime[1], runtime[18], std::make_shared<Character>(U'Q'),
       std::make_shared<Character>(U'q'), std::make_shared<Character>(U'A'),
       std::make_shared<Character>(U'a')},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("4≡÷0.25") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "4≡÷0.25");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[3], runtime[18], 4, 0.25},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("∞≡÷0") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "∞≡÷0");
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[3], runtime[18], std::make_shared<Number>(1.0 / 0.0), 0},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡÷∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡÷∞");
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[3], runtime[18], 0, std::make_shared<Number>(1.0 / 0.0)},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡⋆0") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡⋆0");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[4], runtime[18], 1, 0},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯1≡¯1⋆5") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯1≡¯1⋆5");
  CompileParams p{{0, 3, 0, 0, 0, 2, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[4], runtime[18], -1, 5},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡¯1⋆¯6") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡¯1⋆¯6");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[4], runtime[18], 1, -1, -6},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("3≡⌊3.9") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "3≡⌊3.9");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[6], runtime[18], 3, 3.9},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯4≡⌊¯3.9") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯4≡⌊¯3.9");
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[6], runtime[18], -4, -3.9},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("∞≡⌊∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "∞≡⌊∞");
  CompileParams p{
      {0, 2, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[6], runtime[18], std::make_shared<Number>(1.0 / 0.0)},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯∞≡⌊¯∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯∞≡⌊¯∞");
  CompileParams p{
      {0, 2, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[6], runtime[18], std::make_shared<Number>(-1.0 / 0.0)},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("¯1e30≡⌊¯1e30") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "¯1e30≡⌊¯1e30");
  CompileParams p{{0, 2, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[6], runtime[18], -1e30},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡1=1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡1=1");
  CompileParams p{{0, 2, 0, 0, 0, 2, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[15], runtime[18], 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡¯1=∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡¯1=∞");
  CompileParams p{
      {0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
      {runtime[15], runtime[18], 0, -1, std::make_shared<Number>(1.0 / 0.0)},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡'a'='a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡'a'='a'");
  CompileParams p{
      {0, 3, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
      {runtime[15], runtime[18], 1, std::make_shared<Character>(U'a')},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡'a'='A'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡'a'='A'");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[15], runtime[18], 0,
                   std::make_shared<Character>(U'a'),
                   std::make_shared<Character>(U'A')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡{F←+⋄f=f}") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡{F←+⋄f=f}");
  CompileParams p{{1,  1, 0,  2, 0, 3, 17, 7,  0, 0, 33, 0, 0,
                   48, 6, 32, 0, 0, 0, 1,  34, 0, 0, 17, 7},
                  {runtime[0], runtime[15], runtime[18], 1},
                  {{0, 1, 0}, {0, 1, 1}},
                  {{0, 0}, {8, 1}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡{a‿b←⟨+´,+´⟩⋄a=b}") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡{a‿b←⟨+´,+´⟩⋄a=b}");
  CompileParams p{{1,  1, 0,  2,  0,  4, 17, 7,  0, 3,  0,  0, 26, 0,
                   3,  0, 0,  26, 11, 2, 33, 0,  0, 33, 0,  1, 12, 2,
                   48, 6, 34, 0,  1,  0, 1,  34, 0, 0,  17, 7},
                  {runtime[0], runtime[15], runtime[18], runtime[50], 1},
                  {{0, 1, 0}, {0, 1, 1}},
                  {{0, 0}, {8, 2}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡{_op←{𝕗}⋄op='o'}") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡{_op←{𝕗}⋄op='o'}");
  CompileParams p{
      {1, 1, 0, 1, 0, 2,  17, 7, 1,  2, 33, 0, 0, 48,
       6, 0, 3, 0, 0, 34, 0,  0, 17, 7, 34, 0, 1, 7},
      {runtime[15], runtime[18], 0, std::make_shared<Character>(U'o')},
      {{0, 1, 0}, {0, 1, 1}, {1, 1, 2}},
      {{0, 0}, {8, 1}, {24, 2}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡{F←{𝕩}⋄G←{𝕩}⋄f=g}") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡{F←{𝕩}⋄G←{𝕩}⋄f=g}");
  CompileParams p{{1, 1, 0,  1,  0,  2, 17, 7, 1,  2, 33, 0, 0, 48,
                   6, 1, 3,  33, 0,  1, 48, 6, 34, 0, 1,  0, 0, 34,
                   0, 0, 17, 7,  34, 0, 1,  7, 34, 0, 1,  7},
                  {runtime[15], runtime[18], 0},
                  {{0, 1, 0}, {0, 1, 1}, {0, 0, 2}, {0, 0, 3}},
                  {{0, 0}, {8, 2}, {32, 3}, {36, 3}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡{F←{𝕩}⋄f=f}") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡{F←{𝕩}⋄f=f}");
  CompileParams p{{1,  1, 0, 1, 0, 2,  17, 7, 1,  2, 33, 0, 0, 48, 6,
                   32, 0, 0, 0, 0, 34, 0,  0, 17, 7, 34, 0, 1, 7},
                  {runtime[15], runtime[18], 1},
                  {{0, 1, 0}, {0, 1, 1}, {0, 0, 2}},
                  {{0, 0}, {8, 1}, {25, 3}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡1≤1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡1≤1");
  CompileParams p{{0, 2, 0, 0, 0, 2, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[16], runtime[18], 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡¯∞≤¯1e3") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡¯∞≤¯1e3");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[16], runtime[18], 1,
                   std::make_shared<Number>(-1.0 / 0.0), -1000},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡∞≤¯∞") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡∞≤¯∞");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[16], runtime[18], 0,
                   std::make_shared<Number>(1.0 / 0.0),
                   std::make_shared<Number>(-1.0 / 0.0)},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡∞≤@") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡∞≤@");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[16], runtime[18], 1,
                   std::make_shared<Number>(1.0 / 0.0),
                   std::make_shared<Character>(U'\0')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡'z'≤¯0.5") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡'z'≤¯0.5");
  CompileParams p{
      {0, 3, 0, 0, 0, 4, 17, 0, 1, 0, 2, 17, 7},
      {runtime[16], runtime[18], 0, -0.5, std::make_shared<Character>(U'z')},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡'a'≤'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡'a'≤'a'");
  CompileParams p{
      {0, 3, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
      {runtime[16], runtime[18], 1, std::make_shared<Character>(U'a')},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0≡'c'≤'a'") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "0≡'c'≤'a'");
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[16], runtime[18], 0,
                   std::make_shared<Character>(U'c'),
                   std::make_shared<Character>(U'a')},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨⟩≡≢<2") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨⟩≡≢<2");
  CompileParams p{{0, 3, 0, 0, 16, 0, 2, 16, 0, 1, 11, 0, 17, 7},
                  {runtime[12], runtime[18], runtime[19], 2},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨3⟩≡≢\"abc\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨3⟩≡≢\"abc\"");
  CompileParams p{
      {0, 3, 0, 1, 16, 0, 0, 0, 2, 11, 1, 17, 7},
      {runtime[18], runtime[19], 3, std::make_shared<Array>(U"abc")},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨2,3⟩≡≢>\"abc\"‿\"fed\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨2,3⟩≡≢>\"abc\"‿\"fed\"");
  CompileParams p{
      {0, 5, 0, 6, 11, 2, 0, 0, 16, 0, 2, 16, 0, 1, 0, 3, 0, 4, 11, 2, 17, 7},
      {runtime[13], runtime[18], runtime[19], 2, 3,
       std::make_shared<Array>(U"abc"), std::make_shared<Array>(U"fed")},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨2,3,4,5⟩≡≢2‿3‿4‿5⥊↕120") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨2,3,4,5⟩≡≢2‿3‿4‿5⥊↕120");
  CompileParams p{
      {0, 8, 0,  3, 16, 0, 2, 0, 4, 0, 5, 0, 6, 0,  7, 11, 4, 17,
       0, 1, 16, 0, 0,  0, 4, 0, 5, 0, 6, 0, 7, 11, 4, 17, 7},
      {runtime[18], runtime[19], runtime[22], runtime[28], 2, 3, 4, 5, 120},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨6⟩≡≢⥊>\"abc\"‿\"fed\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨6⟩≡≢⥊>\"abc\"‿\"fed\"");
  CompileParams p{{0, 5, 0,  6, 11, 2, 0, 0,  16, 0,  3, 16,
                   0, 2, 16, 0, 1,  0, 4, 11, 1,  17, 7},
                  {runtime[13], runtime[18], runtime[19], runtime[22], 6,
                   std::make_shared<Array>(U"abc"),
                   std::make_shared<Array>(U"fed")},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("\"abc\"≡0⊑\"abc\"‿\"de\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"abc\"≡0⊑\"abc\"‿\"de\"");
  CompileParams p{{0, 3, 0, 4, 11, 2, 0, 1, 0, 2, 17, 0, 0, 0, 3, 17, 7},
                  {runtime[18], runtime[37], 0, std::make_shared<Array>(U"abc"),
                   std::make_shared<Array>(U"de")},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("\"de\"≡1⊑\"abc\"‿\"de\"") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "\"de\"≡1⊑\"abc\"‿\"de\"");
  CompileParams p{{0, 4, 0, 3, 11, 2, 0, 1, 0, 2, 17, 0, 0, 0, 3, 17, 7},
                  {runtime[18], runtime[37], 1, std::make_shared<Array>(U"de"),
                   std::make_shared<Array>(U"abc")},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨⟩≡↕0") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨⟩≡↕0");
  CompileParams p{{0, 2, 0, 1, 16, 0, 0, 11, 0, 17, 7},
                  {runtime[18], runtime[28], 0},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨0⟩≡↕1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨0⟩≡↕1");
  CompileParams p{{0, 3, 0, 1, 16, 0, 0, 0, 2, 11, 1, 17, 7},
                  {runtime[18], runtime[28], 0, 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⟨0,1,2,3,4,5,6⟩≡↕7") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨0,1,2,3,4,5,6⟩≡↕7");
  CompileParams p{{0, 9, 0, 1, 16, 0, 0, 0, 2,  0, 3,  0, 4,
                   0, 5, 0, 6, 0,  7, 0, 8, 11, 7, 17, 7},
                  {runtime[18], runtime[28], 0, 1, 2, 3, 4, 5, 6, 7},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡!1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡!1");
  CompileParams p{{0, 2, 0, 1, 16, 0, 0, 0, 2, 17, 7},
                  {runtime[18], runtime[43], 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("1≡'e'!1") {
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "1≡'e'!1");
  CompileParams p{
      {0, 2, 0, 1, 0, 3, 17, 0, 0, 0, 2, 17, 7},
      {runtime[18], runtime[43], 1, std::make_shared<Character>(U'e')},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}