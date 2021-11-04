
#include "utils.hpp"
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("0≡¯2+2") {
  spdlog::critical("test='{}', ans='{}'", "0≡¯2+2", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[0], runtime[18], 0, -2, 2},
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

TEST_CASE("1e4≡5e3+5e3") {
  spdlog::critical("test='{}', ans='{}'", "1e4≡5e3+5e3", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[0], runtime[18], 10000, 5000},
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

TEST_CASE("'c'≡'a'+2") {
  spdlog::critical("test='{}', ans='{}'", "'c'≡'a'+2", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 2, 0, 0, 0, 4, 17, 0, 1, 0, 3, 17, 7},
      {runtime[0], runtime[18], 2, new Character('c'), new Character('a')},
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

TEST_CASE("'a'≡¯2+'c'") {
  spdlog::critical("test='{}', ans='{}'", "'a'≡¯2+'c'", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 4, 0, 0, 0, 2, 17, 0, 1, 0, 3, 17, 7},
      {runtime[0], runtime[18], -2, new Character('a'), new Character('c')},
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

TEST_CASE("'a'+'c'") {
  spdlog::critical("test='{}', ans='{}'", "'a'+'c'", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[0], new Character('a'), new Character('c')},
                  {{0, 1, 0}},
                  {{0, 0}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←-⋄f+2") {
  spdlog::critical("test='{}', ans='{}'", "F←-⋄f+2", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 33, 0, 0, 48, 6, 0, 2, 0, 0, 34, 0, 0, 17, 7},
                  {runtime[0], runtime[1], 2},
                  {{0, 1, 0}},
                  {{0, 1}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("¯∞≡1e6-∞") {
  spdlog::critical("test='{}', ans='{}'", "¯∞≡1e6-∞", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], new Number(-1.0 / 0.0), 1000000,
                   new Number(1.0 / 0.0)},
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

TEST_CASE("4≡-¯4") {
  spdlog::critical("test='{}', ans='{}'", "4≡-¯4", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], 4, -4},
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

TEST_CASE("¯∞≡-∞") {
  spdlog::critical("test='{}', ans='{}'", "¯∞≡-∞", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[1], runtime[18], new Number(-1.0 / 0.0), new Number(1.0 / 0.0)},
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

TEST_CASE("∞≡-¯∞") {
  spdlog::critical("test='{}', ans='{}'", "∞≡-¯∞", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 3, 0, 0, 16, 0, 1, 0, 2, 17, 7},
      {runtime[1], runtime[18], new Number(1.0 / 0.0), new Number(-1.0 / 0.0)},
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

TEST_CASE("4≡9-5") {
  spdlog::critical("test='{}', ans='{}'", "4≡9-5", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
                  {runtime[1], runtime[18], 4, 9, 5},
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

TEST_CASE("@≡'a'-97") {
  spdlog::critical("test='{}', ans='{}'", "@≡'a'-97", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 2, 0, 0, 0, 4, 17, 0, 1, 0, 3, 17, 7},
      {runtime[1], runtime[18], 97, new Character('\0'), new Character('a')},
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

TEST_CASE("3≡'d'-'a'") {
  spdlog::critical("test='{}', ans='{}'", "3≡'d'-'a'", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
      {0, 4, 0, 0, 0, 3, 17, 0, 1, 0, 2, 17, 7},
      {runtime[1], runtime[18], 3, new Character('d'), new Character('a')},
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

TEST_CASE("'Q'≡'q'+'A'-'a'") {
  spdlog::critical("test='{}', ans='{}'", "'Q'≡'q'+'A'-'a'", "1");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 6, 0, 1, 0, 5, 17, 0, 0, 0, 4, 17, 0, 2, 0, 3, 17, 7},
                  {runtime[0], runtime[1], runtime[18], new Character('Q'),
                   new Character('q'), new Character('A'), new Character('a')},
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

TEST_CASE("97-'a'") {
  spdlog::critical("test='{}', ans='{}'", "97-'a'", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 2, 0, 0, 0, 1, 17, 7},
                  {runtime[1], 97, new Character('a')},
                  {{0, 1, 0}},
                  {{0, 0}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("@-1") {
  spdlog::critical("test='{}', ans='{}'", "@-1", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 0, 0, 0, 2, 17, 7},
                  {runtime[1], 1, new Character('\0')},
                  {{0, 1, 0}},
                  {{0, 0}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("-'a'") {
  spdlog::critical("test='{}', ans='{}'", "-'a'", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 0, 0, 16, 7},
                  {runtime[1], new Character('a')},
                  {{0, 1, 0}},
                  {{0, 0}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("F←÷⋄-f") {
  spdlog::critical("test='{}', ans='{}'", "F←÷⋄-f", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 1, 33, 0, 0, 48, 6, 34, 0, 0, 0, 0, 16, 7},
                  {runtime[1], runtime[3]},
                  {{0, 1, 0}},
                  {{0, 1}}

  };

  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}
