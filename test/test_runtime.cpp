#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Evaluate Runtime") {
  const auto _provide = provides::get_provides();
  const auto provide = _provide->values;
  auto rcu =
#include <cxbqn/__/r>
  };

  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
}

TEST_CASE("Check valence after loading runtime") {
  spdlog::critical("test '{𝕏0}{𝕨{𝕩}⊘{𝕨}𝕏}7', ans '7'");
  const auto runtime = provides::get_runtime()->values;
  auto rcu =
      {0, 2, 1,  1, 16, 1, 2,  16, 7, 34, 0, 1,  1, 3, 0, 0,  1, 4, 27, 34,
       0, 2, 23, 7, 0,  1, 34, 0,  1, 16, 7, 34, 0, 2, 7, 34, 0, 1, 7},
      {runtime[58], 0, 7},
      {{0, 1, 0}, {0, 0, 1}, {0, 0, 2}, {0, 0, {{}, {3}}}, {0, 0, 4}},
      {{0, 0}, {9, 3}, {24, 3}, {31, 3}, {35, 3}}};
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dyncast<Number>(ret.v);
  REQUIRE(nullptr != n);
  REQUIRE(7 == doctest::Approx(n->v));
}
