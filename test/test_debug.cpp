#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE(
    "(↕6)≡⟜(≠¨)○(2‿3⊸⥊)⟨⟩‿\"a\"‿\"ab\"‿\"abc\"‿\"abcd\"‿\"abcde\"‿\"abcdef\"") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'",
                   "(↕6)≡⟜(≠¨)○(2‿3⊸⥊)"
                   "⟨⟩‿\"a\"‿\"ab\"‿\"abc\"‿\"abcd\"‿\"abcde\"‿\"abcdef\"");
  CompileParams p{
      {11, 0,  0, 11, 0, 12, 0,  13, 0,  14, 0,  15, 0,  16, 11, 7,
       0,  2,  0, 6,  0, 9,  0,  10, 11, 2,  27, 0,  5,  0,  4,  0,
       0,  26, 0, 7,  0, 1,  27, 27, 0,  8,  0,  3,  16, 17, 7},
      {runtime[14], runtime[18], runtime[22], runtime[28], runtime[47],
       runtime[54], runtime[55], runtime[56], 6, 2, 3,
       std::make_shared<Array>(U"a"), std::make_shared<Array>(U"ab"),
       std::make_shared<Array>(U"abc"), std::make_shared<Array>(U"abcd"),
       std::make_shared<Array>(U"abcde"), std::make_shared<Array>(U"abcdef")},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("≡⟜(≠¨)4‿0‿2⥊↕0") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "≡⟜(≠¨)4‿0‿2⥊↕0");
  CompileParams p{{0, 7,  0, 3, 16, 0, 2,  0, 6, 0, 7, 0,  8,  11,
                   3, 17, 0, 4, 0,  0, 26, 0, 5, 0, 1, 27, 16, 7},
                  {runtime[14], runtime[18], runtime[22], runtime[28],
                   runtime[47], runtime[56], 4, 0, 2},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("((+⌜˜≠¨)≡(≠¨∾⌜˜))\"\"‿⟨2,3⟩‿\"abcde\"") {
  spdlog::critical("test='{}'", "((+⌜˜≠¨)≡(≠¨∾⌜˜))\"\"‿⟨2,3⟩‿\"abcde\"");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{{0, 9, 0,  7,  0,  8, 11, 2, 0, 10, 11, 3,  0,  4,  0,
                   6, 0, 3,  26, 26, 0, 5,  0, 1, 26, 20, 0,  2,  0,  5,
                   0, 1, 26, 0,  4,  0, 6,  0, 0, 26, 26, 20, 21, 16, 7},
                  {runtime[0], runtime[14], runtime[18], runtime[23],
                   runtime[45], runtime[47], runtime[48], 2, 3,
                   std::make_shared<Array>(U""),
                   std::make_shared<Array>(U"abcde")},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<-2)≡-¨2") {
  spdlog::critical("test='{}'", "(<-2)≡-¨2");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 4, 0, 3, 0, 0, 26, 16, 0, 2, 0, 4, 0, 0, 16, 0, 1, 16, 17, 7},
      {runtime[1], runtime[12], runtime[18], runtime[47], 2},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<<2)≡<¨2") {
  spdlog::critical("test='{}'", "(<<2)≡<¨2");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 3, 0, 2, 0, 0, 26, 16, 0, 1, 0, 3, 0, 0, 16, 0, 0, 16, 17, 7},
      {runtime[12], runtime[18], runtime[47], 2},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE(
    "⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩") {
  spdlog::critical(
      "test='{}'",
      "⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  4, 0, 0,  16, 0,  5,  0, 0, 16, 0, 6,  0,  0,  16, 0,  4,  0, 7,  0,
       6,  0, 7, 11, 4,  0,  2,  0, 6, 0,  6, 11, 2,  17, 0,  3,  0,  0, 26, 16,
       11, 3, 0, 8,  0,  0,  16, 0, 9, 0,  0, 16, 11, 2,  11, 3,  0,  0, 16, 0,
       1,  0, 4, 0,  5,  0,  6,  0, 4, 0,  7, 0,  6,  0,  7,  11, 4,  0, 2,  0,
       6,  0, 6, 11, 2,  17, 11, 3, 0, 8,  0, 9,  11, 2,  11, 3,  17, 7},
      {runtime[1], runtime[18], runtime[22], runtime[47], 1, 3, 2, 0, 5, 4},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<-4)≡-<4") {
  spdlog::critical("test='{}'", "(<-4)≡-<4");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 3, 0, 1, 16, 0, 0, 16, 0, 2, 0, 3, 0, 0, 16, 0, 1, 16, 17, 7},
      {runtime[1], runtime[12], runtime[18], 4},
      {{0, 1, 0}},
      {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(<2)≡1+<1") {
  spdlog::critical("test='{}'", "(<2)≡1+<1");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 1, 16, 0, 0, 0, 4, 17, 0, 2, 0, 3, 0, 1, 16, 17, 7},
                  {runtime[0], runtime[12], runtime[18], 2, 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

