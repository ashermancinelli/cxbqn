
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
