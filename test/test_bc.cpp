/*
 * This file is generated, don't edit!
 * Generated by the CXBQN build system on 2021-11-20T18:26:51
 */
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("5                     #  0 PUSH,  7 RETN") {
  spdlog::critical("test='{}', ans='{}'",
                   "5                     #  0 PUSH,  7 RETN", "5");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 7}, {5}, {{0, 1, 0}}, {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5 == doctest::Approx(n->v));
}

TEST_CASE("4⋄3                   #  6 POPS") {
  spdlog::critical("test='{}', ans='{}'", "4⋄3                   #  6 POPS",
                   "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 6, 0, 1, 7}, {4, 3}, {{0, 1, 0}}, {{0, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("a←5                   # 33 VARM, 48 SETN") {
  spdlog::critical("test='{}', ans='{}'",
                   "a←5                   # 33 VARM, 48 SETN", "5");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0, 48, 7}, {5}, {{0, 1, 0}}, {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5 == doctest::Approx(n->v));
}

TEST_CASE("a←5⋄a↩4               # 49 SETU") {
  spdlog::critical("test='{}', ans='{}'", "a←5⋄a↩4               # 49 SETU",
                   "4");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0, 48, 6, 0, 1, 33, 0, 0, 49, 7},
                  {5, 4},
                  {{0, 1, 0}},
                  {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4 == doctest::Approx(n->v));
}

TEST_CASE("a←2⋄b←3⋄a             # 32 VARO") {
  spdlog::critical("test='{}', ans='{}'", "a←2⋄b←3⋄a             # 32 VARO",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0, 48, 6, 0, 1, 33, 0, 1, 48, 6, 34, 0, 0, 7},
                  {2, 3},
                  {{0, 1, 0}},
                  {{0, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("a←1⋄A 4               # 16 FN1C") {
  spdlog::critical("test='{}', ans='{}'", "a←1⋄A 4               # 16 FN1C",
                   "1");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0, 48, 6, 0, 1, 34, 0, 0, 16, 7},
                  {1, 4},
                  {{0, 1, 0}},
                  {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("a←2⋄3 A 4             # 17 FN2C") {
  spdlog::critical("test='{}', ans='{}'", "a←2⋄3 A 4             # 17 FN2C",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0, 48, 6, 0, 2, 34, 0, 0, 0, 1, 17, 7},
                  {2, 3, 4},
                  {{0, 1, 0}},
                  {{0, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("{𝕩}6                  #  1 DFND") {
  spdlog::critical("test='{}', ans='{}'", "{𝕩}6                  #  1 DFND",
                   "6");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 1, 1, 16, 7, 34, 0, 1, 7},
                  {6},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 0}, {6, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6 == doctest::Approx(n->v));
}

TEST_CASE("A←{𝕨}⋄3 A 4           #    dyadic block function") {
  spdlog::critical("test='{}', ans='{}'",
                   "A←{𝕨}⋄3 A 4           #    dyadic block function", "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {1, 1, 33, 0, 0, 48, 6, 0, 1, 34, 0, 0, 0, 0, 17, 7, 34, 0, 2, 7},
      {3, 4},
      {{0, 1, 0}, {0, 0, {{}, {1}}}},
      {{0, 1}, {16, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("a‿b←7‿2⋄a             # 11 ARRO, 12 ARRM") {
  spdlog::critical("test='{}', ans='{}'",
                   "a‿b←7‿2⋄a             # 11 ARRO, 12 ARRM", "7");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 0, 0, 1, 11, 2, 33, 0, 0, 33, 0, 1, 12, 2, 48, 6, 34, 0, 0, 7},
      {7, 2},
      {{0, 1, 0}},
      {{0, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(7 == doctest::Approx(n->v));
}

TEST_CASE("0{𝕨𝕏1}2               # 19 FN2O (doesn't test call type)") {
  spdlog::critical("test='{}', ans='{}'",
                   "0{𝕨𝕏1}2               # 19 FN2O (doesn't test call type)",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 2, 1, 1, 0, 0, 17, 7, 0, 1, 34, 0, 1, 34, 0, 2, 19, 7},
                  {0, 1, 2},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 0}, {8, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("{({𝕨}𝕨)𝕏𝕩}5           # 18 FN1O not called") {
  spdlog::critical("test='{}', ans='{}'",
                   "{({𝕨}𝕨)𝕏𝕩}5           # 18 FN1O not called", "5");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0,  0, 1, 1, 16, 7,  32, 0, 1,  34, 0, 1,
                   34, 0, 2, 1, 2,  18, 19, 7, 34, 0,  2, 7},
                  {5},
                  {{0, 1, 0}, {0, 0, 1}, {0, 0, {{}, {2}}}},
                  {{0, 0}, {6, 3}, {20, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5 == doctest::Approx(n->v));
}

TEST_CASE("{𝕩{a‿b←𝕨}𝕨,𝕩}8        # 19 FN2O not called") {
  spdlog::critical("test='{}', ans='{}'",
                   "{𝕩{a‿b←𝕨}𝕨,𝕩}8        # 19 FN2O not called", "8");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 1, 1,  16, 7, 34, 0, 2, 1,  2, 32, 0,  1, 19, 6, 34,
                   0, 1, 7, 34, 0,  2, 33, 0, 3, 33, 0, 4,  12, 2, 48, 7},
                  {8},
                  {{0, 1, 0}, {0, 0, 1}, {0, 0, {{}, {2}}}},
                  {{0, 0}, {6, 3}, {20, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(8 == doctest::Approx(n->v));
}

TEST_CASE("4{𝔽}                  # 26 MD1C") {
  spdlog::critical("test='{}', ans='{}'", "4{𝔽}                  # 26 MD1C",
                   "4");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{1, 1, 0, 0, 26, 7, 34, 0, 1, 7},
                  {4},
                  {{0, 1, 0}, {1, 1, 1}},
                  {{0, 0}, {6, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4 == doctest::Approx(n->v));
}

TEST_CASE("4{𝔽⋄𝕩}6               #    deferred modifier") {
  spdlog::critical("test='{}', ans='{}'",
                   "4{𝔽⋄𝕩}6               #    deferred modifier", "6");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 1, 1, 0, 0, 26, 16, 7, 34, 0, 4, 6, 34, 0, 1, 7},
                  {4, 6},
                  {{0, 1, 0}, {1, 0, 1}},
                  {{0, 0}, {9, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6 == doctest::Approx(n->v));
}

TEST_CASE("3{𝔾}{𝕩} 1             # 27 MD2C") {
  spdlog::critical("test='{}', ans='{}'", "3{𝔾}{𝕩} 1             # 27 MD2C",
                   "1");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 1, 1, 1, 2, 0, 0, 27, 16, 7, 34, 0, 1, 7, 34, 0, 2, 7},
                  {3, 1},
                  {{0, 1, 0}, {0, 0, 1}, {2, 1, 2}},
                  {{0, 0}, {11, 3}, {15, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("(2{𝔽}{𝕩})3            # 20 TR2D") {
  spdlog::critical("test='{}', ans='{}'", "(2{𝔽}{𝕩})3            # 20 TR2D",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1, 1, 1, 1, 2, 0, 0, 26, 20, 16, 7, 34, 0, 1, 7, 34, 0, 1, 7},
      {2, 3},
      {{0, 1, 0}, {0, 0, 1}, {1, 1, 2}},
      {{0, 0}, {12, 3}, {16, 2}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("3({a‿b←𝕩⋄a}{𝕨‿𝕩})4    #    dyadic 2-train") {
  spdlog::critical("test='{}', ans='{}'",
                   "3({a‿b←𝕩⋄a}{𝕨‿𝕩})4    #    dyadic 2-train", "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1,  1, 1, 1,  2, 20, 0,  0, 17, 7,  34, 0,  2, 34, 0, 1, 11, 2,
       7, 34, 0, 1, 33, 0, 3,  33, 0, 4,  12, 2,  48, 6, 34, 0, 3, 7},
      {3, 4},
      {{0, 1, 0}, {0, 0, {{}, {1}}}, {0, 0, 2}},
      {{0, 0}, {11, 3}, {20, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("4({𝕨‿𝕩}{𝕩}{𝕨})5       # 21 TR3D") {
  spdlog::critical("test='{}', ans='{}'", "4({𝕨‿𝕩}{𝕩}{𝕨})5       # 21 TR3D",
                   "4");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 1,  1, 1, 2, 1,  3, 21, 0,  0, 17, 7,  34, 0,
                   2, 7, 34, 0, 1, 7, 34, 0, 2,  34, 0, 1,  11, 2,  7},
                  {4, 5},
                  {{0, 1, 0}, {0, 0, {{}, {1}}}, {0, 0, 2}, {0, 0, {{}, {3}}}},
                  {{0, 0}, {13, 3}, {17, 3}, {21, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4 == doctest::Approx(n->v));
}

TEST_CASE("a‿b←(2{𝕨‿𝕩}{𝕩})5⋄a    #    monadic, data in left branch") {
  spdlog::critical("test='{}', ans='{}'",
                   "a‿b←(2{𝕨‿𝕩}{𝕩})5⋄a    #    monadic, data in left branch",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1,  1, 1, 1, 2,  0, 0, 21, 16, 33, 0, 0,  33, 0, 1,  12, 2, 48,
       6, 34, 0, 0, 7, 34, 0, 1, 7,  34, 0,  2, 34, 0,  1, 11, 2,  7},
      {2, 5},
      {{0, 1, 0}, {0, 0, 1}, {0, 0, {{}, {2}}}},
      {{0, 2}, {24, 3}, {28, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("({a↩2⋄𝕩}{𝕩⋄a}{a↩3⋄𝕩})a←4 # ordering") {
  spdlog::critical("test='{}', ans='{}'", "({a↩2⋄𝕩}{𝕩⋄a}{a↩3⋄𝕩})a←4 # ordering",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0,  2, 33, 0, 0, 48, 1,  1,  1, 2,  1, 3,  21, 16, 7,
                   0,  1, 33, 1, 0, 49, 6,  34, 0, 1,  7, 34, 0,  1,  6,
                   32, 1, 0,  7, 0, 0,  33, 1,  0, 49, 6, 34, 0,  1,  7},
                  {2, 3, 4},
                  {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}},
                  {{0, 1}, {15, 3}, {26, 3}, {34, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("a←3⋄a{𝕩}↩8⋄a          # 50 SETM") {
  spdlog::critical("test='{}', ans='{}'", "a←3⋄a{𝕩}↩8⋄a          # 50 SETM",
                   "8");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0,  48, 6, 0, 1,  1, 1, 33,
                   0, 0, 50, 6, 34, 0,  0, 7, 34, 0, 1, 7},
                  {3, 8},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 1}, {20, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(8 == doctest::Approx(n->v));
}

TEST_CASE("a←4⋄a{𝕨⋄5}↩6          #    returns new value") {
  spdlog::critical("test='{}', ans='{}'",
                   "a←4⋄a{𝕨⋄5}↩6          #    returns new value", "5");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0, 33, 0, 0,  48, 6, 0, 2, 1, 1, 33,
                   0, 0, 50, 7, 34, 0,  2, 6, 0, 1, 7},
                  {4, 5, 6},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 1}, {16, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5 == doctest::Approx(n->v));
}

TEST_CASE("a←3⋄a{𝕩⋄1}↩⋄a         # 51 SETC") {
  spdlog::critical("test='{}', ans='{}'", "a←3⋄a{𝕩⋄1}↩⋄a         # 51 SETC",
                   "1");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0,  33, 0, 0, 48, 6, 1, 1, 33, 0, 0, 51,
                   6, 34, 0,  0, 7, 34, 0, 1, 6, 0,  1, 7},
                  {3, 1},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 1}, {18, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("a‿b←2‿1⋄a‿b{𝕩‿𝕨}↩4⋄a  #    lists") {
  spdlog::critical("test='{}', ans='{}'", "a‿b←2‿1⋄a‿b{𝕩‿𝕨}↩4⋄a  #    lists",
                   "4");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0,  0, 0, 1, 11, 2,  33, 0,  0,  33, 0,  1,  12, 2,  48,
                   6,  0, 2, 1, 1,  33, 0,  0,  33, 0,  1,  12, 2,  50, 6,
                   34, 0, 0, 7, 34, 0,  1,  34, 0,  2,  11, 2,  7},
                  {2, 1, 4},
                  {{0, 1, 0}, {0, 0, {{}, {1}}}},
                  {{0, 2}, {34, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4 == doctest::Approx(n->v));
}

TEST_CASE("     {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type") {
  spdlog::critical("test='{}', ans='{}'",
                   "     {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type", "7");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 0,  1, 1, 16, 7,  34, 0,  1,  1,  2, 34, 0, 2, 19,
                   7, 34, 0, 1, 33, 0,  3,  48, 6,  34, 0, 2,  1, 3, 18,
                   6, 32, 0, 3, 7,  34, 0,  1,  33, 1,  3, 49, 7},
                  {7},
                  {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}},
                  {{0, 0}, {6, 3}, {16, 4}, {35, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(7 == doctest::Approx(n->v));
}

TEST_CASE("    3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type") {
  spdlog::critical("test='{}', ans='{}'",
                   "    3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type", "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{{0, 1,  1, 1,  0, 0, 17, 7,  34, 0,  1,  1,  2, 34, 0,
                   2, 19, 7, 34, 0, 1, 33, 0,  3,  48, 6,  34, 0, 2,  1,
                   3, 18, 6, 32, 0, 3, 7,  34, 0,  1,  33, 1,  3, 49, 7},
                  {3, 7},
                  {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}},
                  {{0, 0}, {8, 3}, {18, 4}, {37, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("{𝕏0} {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type") {
  spdlog::critical("test='{}', ans='{}'",
                   "{𝕏0} {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type", "7");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1, 1, 1,  16, 1,  2,  16, 7,  34, 0, 1,  1,  3, 34, 0,  2,  23,
       7, 0, 0, 34, 0,  1,  16, 7,  34, 0,  1, 33, 0,  3, 48, 6,  34, 0,
       2, 1, 4, 18, 6,  32, 0,  3,  7,  34, 0, 1,  33, 1, 3,  49, 7},
      {0, 7},
      {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}},
      {{0, 0}, {9, 3}, {19, 3}, {26, 4}, {45, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(7 == doctest::Approx(n->v));
}

TEST_CASE("{𝕏0}3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type") {
  spdlog::critical("test='{}', ans='{}'",
                   "{𝕏0}3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type", "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  2, 1, 1,  0,  1,  17, 1,  2, 16, 7, 34, 0,  1, 1, 3,  34, 0,  2,
       23, 7, 0, 0,  34, 0,  1,  16, 7, 34, 0, 1,  33, 0, 3, 48, 6,  34, 0,
       2,  1, 4, 18, 6,  32, 0,  3,  7, 34, 0, 1,  33, 1, 3, 49, 7},
      {0, 3, 7},
      {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}},
      {{0, 0}, {11, 3}, {21, 3}, {28, 4}, {47, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("a←1⋄{a←2}⋄a") {
  spdlog::critical("test='{}', ans='{}'", "a←1⋄{a←2}⋄a", "1");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 0, 33, 0, 0, 48, 6, 1, 1, 6, 34, 0, 0, 7, 0, 1, 33, 0, 0, 48, 7},
      {1, 2},
      {{0, 1, 0}, {0, 1, 1}},
      {{0, 1}, {14, 1}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("a←1⋄{a↩2}⋄a") {
  spdlog::critical("test='{}', ans='{}'", "a←1⋄{a↩2}⋄a", "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 0, 33, 0, 0, 48, 6, 1, 1, 6, 32, 0, 0, 7, 0, 1, 33, 1, 0, 49, 7},
      {1, 2},
      {{0, 1, 0}, {0, 1, 1}},
      {{0, 1}, {14, 0}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}

TEST_CASE("f‿g←{a←2⋄{a↩𝕩}‿{𝕩⋄a}}⋄F 6⋄G 0") {
  spdlog::critical("test='{}', ans='{}'", "f‿g←{a←2⋄{a↩𝕩}‿{𝕩⋄a}}⋄F 6⋄G 0", "6");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {1, 1, 33, 0, 0, 33, 0, 1, 12, 2,  48, 6, 0,  1, 34, 0, 0, 16, 6,
       0, 2, 34, 0, 1, 16, 7, 0, 0,  33, 0,  0, 48, 6, 1,  2, 1, 3,  11,
       2, 7, 34, 0, 1, 33, 1, 0, 49, 7,  34, 0, 1,  6, 32, 1, 0, 7},
      {2, 6, 0},
      {{0, 1, 0}, {0, 1, 1}, {0, 0, 2}, {0, 0, 3}},
      {{0, 2}, {26, 1}, {40, 3}, {48, 3}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6 == doctest::Approx(n->v));
}

TEST_CASE("L←{𝕩{𝕏𝕗}}⋄{𝕏𝕤}L L L 5") {
  spdlog::critical("test='{}', ans='{}'", "L←{𝕩{𝕏𝕗}}⋄{𝕏𝕤}L L L 5", "5");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {1,  1,  33, 0,  0,  48, 6,  0,  0,  32, 0, 0,  16, 32, 0,  0,
       16, 34, 0,  0,  16, 1,  2,  16, 7,  1,  3, 34, 0,  1,  26, 7,
       34, 0,  0,  34, 0,  1,  16, 7,  34, 0,  4, 34, 0,  1,  16, 7},
      {5},
      {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {1, 0, 3}},
      {{0, 1}, {25, 3}, {32, 3}, {40, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5 == doctest::Approx(n->v));
}

TEST_CASE("_l←{𝕩{𝕏𝕗} 𝔽}⋄{𝕏𝕤} {𝕩}_l 3 _l 5") {
  spdlog::critical("test='{}', ans='{}'", "_l←{𝕩{𝕏𝕗} 𝔽}⋄{𝕏𝕤} {𝕩}_l 3 _l 5",
                   "3");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {1, 1,  33, 0, 0, 48, 6, 0,  1,  32, 0,  0, 0,  0,  26, 16, 34, 0, 0,  1,
       2, 26, 16, 1, 3, 16, 7, 34, 0,  4,  1,  4, 34, 0,  1,  26, 20, 7, 34, 0,
       1, 7,  34, 0, 0, 34, 0, 1,  16, 7,  34, 0, 4,  34, 0,  1,  16, 7},
      {3, 5},
      {{0, 1, 0}, {1, 0, 1}, {0, 0, 2}, {0, 0, 3}, {1, 0, 4}},
      {{0, 1}, {27, 5}, {38, 3}, {42, 3}, {50, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3 == doctest::Approx(n->v));
}

TEST_CASE("1{𝕨}{𝔽{𝕩𝔽𝕨}𝔾𝔽}{𝕩}0    # 0≠1 via Church booleans") {
  spdlog::critical("test='{}', ans='{}'",
                   "1{𝕨}{𝔽{𝕩𝔽𝕨}𝔾𝔽}{𝕩}0    # 0≠1 via Church booleans", "1");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 1,  1, 1,  1,  2, 1,  3, 27, 0,  0, 17, 7,  34, 0, 1,
       7, 32, 0, 1,  34, 0, 2,  1, 4,  34, 0, 1,  26, 21, 7, 34,
       0, 2,  7, 34, 0,  2, 34, 0, 4,  34, 0, 1,  17, 7},
      {1, 0},
      {{0, 1, 0}, {0, 0, 1}, {2, 1, 2}, {0, 0, {{}, {3}}}, {1, 0, {{}, {4}}}},
      {{0, 0}, {13, 3}, {17, 3}, {31, 3}, {35, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}

TEST_CASE("0‿(0‿{𝕩}){{a‿b←𝕩⋄t←𝕤⋄{𝕤⋄T↩{𝕤⋄{a‿b←𝕩⋄a}}}{B𝕗}0⋄(T b){a‿b←𝕩⋄𝔽b}}𝕗} "
          "0‿(1‿(2‿(3‿(4‿{𝕩}))))") {
  spdlog::critical("test='{}', ans='{}'",
                   "0‿(0‿{𝕩}){{a‿b←𝕩⋄t←𝕤⋄{𝕤⋄T↩{𝕤⋄{a‿b←𝕩⋄a}}}{B𝕗}0⋄(T "
                   "b){a‿b←𝕩⋄𝔽b}}𝕗} 0‿(1‿(2‿(3‿(4‿{𝕩}))))",
                   "2");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
      {0,  0,  0,  1,  0,  2,  0,  3,  0,  4,  1,  1,  11, 2,  11, 2,  11, 2,
       11, 2,  11, 2,  1,  2,  0,  0,  0,  0,  1,  3,  11, 2,  11, 2,  26, 16,
       7,  34, 0,  1,  7,  34, 0,  1,  1,  4,  16, 7,  34, 0,  1,  7,  34, 0,
       1,  33, 0,  3,  33, 0,  4,  12, 2,  48, 6,  34, 0,  0,  33, 0,  5,  48,
       6,  0,  0,  1,  5,  1,  6,  26, 16, 6,  1,  7,  32, 0,  4,  32, 0,  5,
       16, 26, 7,  34, 0,  1,  32, 1,  4,  16, 7,  34, 0,  0,  6,  1,  8,  33,
       1,  5,  49, 7,  34, 0,  1,  33, 0,  5,  33, 0,  6,  12, 2,  48, 6,  34,
       0,  6,  34, 0,  4,  16, 7,  34, 0,  0,  6,  1,  9,  7,  34, 0,  1,  33,
       0,  3,  33, 0,  4,  12, 2,  48, 6,  34, 0,  3,  7},
      {0, 1, 2, 3, 4},
      {{0, 1, 0},
       {0, 0, 1},
       {1, 1, 2},
       {0, 0, 3},
       {0, 0, 4},
       {1, 1, 5},
       {0, 0, 6},
       {1, 0, 7},
       {0, 0, 8},
       {0, 0, 9}},
      {{0, 0},
       {37, 3},
       {41, 2},
       {48, 3},
       {52, 6},
       {93, 2},
       {101, 3},
       {112, 7},
       {133, 3},
       {140, 5}}

  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2 == doctest::Approx(n->v));
}
