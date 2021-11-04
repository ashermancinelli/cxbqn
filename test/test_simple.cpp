
#include "utils.hpp"
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("1+1") {
  spdlog::critical("test='{}', ans='{}'", "1+1", "2");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1, 0, 0, 0, 1, 17, 7}, {runtime[0], 1}, {{0, 1, 0}}, {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("1⌊-2") {
  spdlog::critical("test='{}', ans='{}'", "1⌊-2", "-2");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[6], 1, 2},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-2 == doctest::Approx(n->v));
}

TEST_CASE("-2⌊1") {
  spdlog::critical("test='{}', ans='{}'", "-2⌊1", "-1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 1, 0, 2, 17, 0, 0, 16, 7},
                  {runtime[1], runtime[6], 2, 1},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-1 == doctest::Approx(n->v));
}

TEST_CASE("(÷2)+(÷3)+(÷6)") {
  spdlog::critical("test='{}', ans='{}'", "(÷2)+(÷3)+(÷6)", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 4, 0, 1, 16, 0, 0, 0, 3, 0, 1, 16, 17, 0, 0, 0, 2, 0, 1, 16, 17, 7},
      {runtime[0], runtime[3], 2, 3, 6},
      {{0, 1, 0}},
      {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("⊢4⊣5") {
  spdlog::critical("test='{}', ans='{}'", "⊢4⊣5", "4");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 0, 2, 17, 0, 1, 16, 7},
                  {runtime[20], runtime[21], 4, 5},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4 == doctest::Approx(n->v));
}

TEST_CASE("sq←√5,⌊9×|5-sq×sq") {
  spdlog::critical("test='{}', ans='{}'", "sq←√5,⌊9×|5-sq×sq", "0");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  5, 0, 2, 16, 33, 0, 0, 48, 6, 32, 0, 0, 0,  1, 34, 0,  0,
       17, 0, 0, 0, 5,  17, 0, 4, 16, 0, 1,  0, 6, 17, 0, 3,  16, 7},
      {runtime[1], runtime[2], runtime[5], runtime[6], runtime[8], 5, 9},
      {{0, 1, 0}},
      {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(0 == doctest::Approx(n->v));
}

TEST_CASE("((-3)+√(3×3)-4×2×1)÷2×2") {
  spdlog::critical("test='{}', ans='{}'", "((-3)+√(3×3)-4×2×1)÷2×2", "-0.5");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  7, 0, 2,  0, 7,  17, 0, 3, 0, 8,  0,  2,  0, 7,
       17, 0, 2, 0,  6, 17, 0,  1, 0, 5, 0,  2,  0,  5, 17,
       17, 0, 4, 16, 0, 0,  0,  5, 0, 1, 16, 17, 17, 7},
      {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5], 3, 4, 2, 1},
      {{0, 1, 0}},
      {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-0.5 == doctest::Approx(n->v));
}

TEST_CASE("a←2,b←3,c←1⋄((-b)+√(b×b)-4×a×c)÷2×a") {
  spdlog::critical("test='{}', ans='{}'", "a←2,b←3,c←1⋄((-b)+√(b×b)-4×a×c)÷2×a",
                   "-0.5");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  5,  33, 0,  0, 48, 6, 0, 6,  33, 0,  1,  48, 6,  0,  7,  33, 0,
       2,  48, 6,  32, 0, 0,  0, 2, 0,  5,  17, 0,  3,  34, 0,  2,  0,  2,
       34, 0,  0,  17, 0, 2,  0, 8, 17, 0,  1,  32, 0,  1,  0,  2,  32, 0,
       1,  17, 17, 0,  4, 16, 0, 0, 34, 0,  1,  0,  1,  16, 17, 17, 7},
      {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5], 2, 3, 1, 4},
      {{0, 1, 0}},
      {{0, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-0.5 == doctest::Approx(n->v));
}

TEST_CASE("b←1+a←1+c←1⋄((-b)+√(b×b)-4×a×c)÷2×a") {
  spdlog::critical("test='{}', ans='{}'", "b←1+a←1+c←1⋄((-b)+√(b×b)-4×a×c)÷2×a",
                   "-0.5");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  5,  33, 0,  0,  48, 0,  0, 0, 5,  17, 33, 0, 1,  48, 0,  0,  0, 5,
       17, 33, 0,  2,  48, 6,  32, 0, 1, 0,  2,  0,  7, 17, 0,  3,  34, 0, 0,
       0,  2,  34, 0,  1,  17, 0,  2, 0, 6,  17, 0,  1, 32, 0,  2,  0,  2, 32,
       0,  2,  17, 17, 0,  4,  16, 0, 0, 34, 0,  2,  0, 1,  16, 17, 17, 7},
      {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5], 1, 4, 2},
      {{0, 1, 0}},
      {{0, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-0.5 == doctest::Approx(n->v));
}

TEST_CASE("b←3⋄⊢d←(b×b)-4×2×1⋄((-b)+√d)÷2×2") {
  spdlog::critical("test='{}', ans='{}'", "b←3⋄⊢d←(b×b)-4×2×1⋄((-b)+√d)÷2×2",
                   "-0.5");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  6,  33, 0,  0,  48, 6, 0, 9, 0,  2,  0,  8,  17, 0,  2, 0,
       7,  17, 0,  1,  32, 0,  0, 0, 2, 32, 0,  0,  17, 17, 33, 0, 1,
       48, 0,  5,  16, 6,  0,  8, 0, 2, 0,  8,  17, 0,  3,  34, 0, 1,
       0,  4,  16, 0,  0,  34, 0, 0, 0, 1,  16, 17, 17, 7},
      {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5], runtime[21],
       3, 4, 2, 1},
      {{0, 1, 0}},
      {{0, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-0.5 == doctest::Approx(n->v));
}

TEST_CASE("a←3,b←4,c←5⋄⊣s←(÷2)×a+b+c⋄√s×(s-a)×(s-b)×(s-c)") {
  spdlog::critical("test='{}', ans='{}'",
                   "a←3,b←4,c←5⋄⊣s←(÷2)×a+b+c⋄√s×(s-a)×(s-b)×(s-c)", "6");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0,  6, 33, 0,  0,  48, 6, 0,  7,  33, 0,  1,  48, 6,  0, 8,
                   33, 0, 2,  48, 6,  32, 0, 2,  0,  0,  32, 0,  1,  17, 0, 0,
                   32, 0, 0,  17, 0,  2,  0, 9,  0,  3,  16, 17, 33, 0,  3, 48,
                   0,  5, 16, 6,  34, 0,  2, 0,  1,  32, 0,  3,  17, 0,  2, 34,
                   0,  1, 0,  1,  32, 0,  3, 17, 17, 0,  2,  34, 0,  0,  0, 1,
                   32, 0, 3,  17, 17, 0,  2, 34, 0,  3,  17, 0,  4,  16, 7},
                  {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5],
                   runtime[20], 3, 4, 5, 2},
                  {{0, 1, 0}},
                  {{0, 4}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6 == doctest::Approx(n->v));
}

TEST_CASE("t←2×5⋄3+(1+(4+(1+5÷t)÷t)÷t)÷t") {
  spdlog::critical("test='{}', ans='{}'", "t←2×5⋄3+(1+(4+(1+5÷t)÷t)÷t)÷t",
                   "3.1415");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  4, 0,  1, 0, 3,  17, 33, 0, 0, 48, 6,  32, 0, 0,  0, 2, 32, 0, 0,
       0,  2, 32, 0, 0, 0,  2,  34, 0, 0, 0,  2,  0,  4, 17, 0, 0, 0,  6, 17,
       17, 0, 0,  0, 7, 17, 17, 0,  0, 0, 6,  17, 17, 0, 0,  0, 5, 17, 7},
      {runtime[0], runtime[2], runtime[3], 2, 5, 3, 1, 4},
      {{0, 1, 0}},
      {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3.1415 == doctest::Approx(n->v));
}

TEST_CASE("3+(1+(4+(1+5÷10)÷10)÷10)÷10") {
  spdlog::critical("test='{}', ans='{}'", "3+(1+(4+(1+5÷10)÷10)÷10)÷10",
                   "3.1415");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 6,  0,  1, 0, 6, 0, 1,  0,  6, 0, 1, 0, 6,  0,  1, 0, 5, 17, 0,  0, 0,
       3, 17, 17, 0, 0, 0, 4, 17, 17, 0, 0, 0, 3, 17, 17, 0, 0, 0, 2,  17, 7},
      {runtime[0], runtime[3], 3, 1, 4, 5, 10},
      {{0, 1, 0}},
      {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3.1415 == doctest::Approx(n->v));
}

TEST_CASE("√25-16") {
  spdlog::critical("test='{}', ans='{}'", "√25-16", "3");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 0, 2, 17, 0, 1, 16, 7},
                  {runtime[1], runtime[5], 25, 16},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("¬15÷20") {
  spdlog::critical("test='{}', ans='{}'", "¬15÷20", "0.25");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 0, 2, 17, 0, 1, 16, 7},
                  {runtime[3], runtime[9], 15, 20},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(0.25 == doctest::Approx(n->v));
}

TEST_CASE("(3∧4)-¬(¬3)∨(¬4)") {
  spdlog::critical("test='{}', ans='{}'", "(3∧4)-¬(¬3)∨(¬4)", "0");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 5,  0, 1, 16, 0, 3, 0, 4, 0, 1,  16, 17, 0,
                   1, 16, 0, 0, 0,  5, 0, 2, 0, 4, 17, 17, 7},
                  {runtime[1], runtime[9], runtime[10], runtime[11], 3, 4},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(0 == doctest::Approx(n->v));
}

TEST_CASE("p←¬q←÷4⋄(q∧q)+(p∨p)") {
  spdlog::critical("test='{}', ans='{}'", "p←¬q←÷4⋄(q∧q)+(p∨p)", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 5, 0,  1, 16, 33, 0, 0, 48, 0, 2, 16, 33, 0,  1, 48, 6,  32, 0, 1,
       0, 4, 34, 0, 1,  17, 0, 0, 32, 0, 0, 0,  3,  34, 0, 0,  17, 17, 7},
      {runtime[0], runtime[3], runtime[9], runtime[10], runtime[11], 4},
      {{0, 1, 0}},
      {{0, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("105¬-3") {
  spdlog::critical("test='{}', ans='{}'", "105¬-3", "109");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[9], 105, 3},
                  {{0, 1, 0}},
                  {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(109 == doctest::Approx(n->v));
}

TEST_CASE("{{-3}+√{3×3}-4×2×1}÷2×2") {
  spdlog::critical("test='{}', ans='{}'", "{{-3}+√{3×3}-4×2×1}÷2×2", "-0.5");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 7,  0, 2, 0, 7, 17, 0, 3, 1,  1, 17, 7, 0, 8,  0,  2, 0,
       7, 17, 0, 2, 0, 6, 17, 0, 1, 1,  2, 17, 0, 4, 16, 0,  0, 1,
       3, 17, 7, 0, 5, 0, 2,  0, 5, 17, 7, 0,  5, 0, 1,  16, 7},
      {runtime[0], runtime[1], runtime[2], runtime[3], runtime[5], 3, 4, 2, 1},
      {{0, 1, 0}, {0, 1, 1}, {0, 1, 2}, {0, 1, 3}},
      {{0, 0}, {13, 0}, {39, 0}, {47, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(-0.5 == doctest::Approx(n->v));
}

TEST_CASE("{a←1⋄{a←2}⋄a}") {
  spdlog::critical("test='{}', ans='{}'", "{a←1⋄{a←2}⋄a}", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{1, 1,  7, 0, 0, 33, 0, 0,  48, 6, 1,  2,
                   6, 34, 0, 0, 7, 0,  1, 33, 0,  0, 48, 7},
                  {1, 2},
                  {{0, 1, 0}, {0, 1, 1}, {0, 1, 2}},
                  {{0, 0}, {3, 1}, {17, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
