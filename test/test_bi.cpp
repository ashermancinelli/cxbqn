#include "utils.hpp"
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("0 +` ↕5") {
  spdlog::critical("test='{}', ans='{}'", "0 +` ↕5", "⟨ 0 1 3 6 10 ⟩");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 1, 16, 0, 2, 0, 0, 26, 0, 3, 17, 7},
                  {runtime[0], runtime[27], runtime[51], 0, 5},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto *a = dynamic_cast<Array *>(ret.v);
  REQUIRE(nullptr != a);
  std::vector<int> ans{0, 1, 3, 6, 10};
  for (int i = 0; i < a->N(); i++) {
    auto *n = dynamic_cast<Number *>(a->values[i]);
    REQUIRE(nullptr != n);
    REQUIRE(ans[i] == doctest::Approx(n->v));
  }
}

TEST_CASE("(↕4) ×⌜ ↕3") {
  spdlog::critical("test='{}', ans='{}'", "(↕4) ×⌜ ↕3",
                   "⟨ 0 0 0 0 1 2 0 2 4 0 3 6 ⟩");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 4, 0, 1, 16, 0, 2, 0, 0, 26, 0, 3, 0, 1, 16, 17, 7},
                  {runtime[2], runtime[27], runtime[47], 4, 3},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto *a = dynamic_cast<Array *>(ret.v);
  REQUIRE(nullptr != a);
  std::vector<int> ans{0, 0, 0, 0, 1, 2, 0, 2, 4, 0, 3, 6};
  std::vector<int> sh{4, 3};

  // Ensure the resulting shape is correct
  for (int i = 0; i < sh.size(); i++)
    CHECK(a->shape[i] == sh[i]);

  // Enusre the values match
  for (int i = 0; i < a->N(); i++) {
    auto *n = dynamic_cast<Number *>(a->values[i]);
    REQUIRE(nullptr != n);
    REQUIRE(ans[i] == doctest::Approx(n->v));
  }
}

TEST_CASE("1 +` 1") {
  spdlog::critical("test='{}', ans='{}'", "1 +` 1", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 2, 0, 0, 26, 16, 0, 1, 16, 7},
                  {runtime[0], runtime[15], runtime[51], 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

TEST_CASE("0‿0 +` 3‿2") {
  spdlog::critical("test='{}', ans='{}'", "0‿0 +` 3‿2", "throws");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 3, 0, 2, 0, 0, 26, 16, 0, 1, 16, 7},
                  {runtime[0], runtime[15], runtime[51], 1},
                  {{0, 1, 0}},
                  {{0, 0}}};
  REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies));
}

#define T "(3‿2⥊1) +` (4‿3‿2⥊1)"
TEST_CASE(T) {
  spdlog::critical("test={}", T);
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{{0, 5,  0, 1, 0, 6, 0, 3, 0, 4, 11, 3, 17, 0,  2, 0,
                   0, 26, 0, 5, 0, 1, 0, 3, 0, 4, 11, 2, 17, 17, 7},
                  {runtime[0], runtime[22], runtime[51], 3, 2, 1, 4},
                  {{0, 1, 0}},
                  {{0, 0}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto *a = dynamic_cast<Array *>(ret.v);
  REQUIRE(nullptr != a);
  std::vector<int> ans{2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
                       4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5};
  std::vector<int> sh{4, 3, 2};

  // Ensure the resulting shape is correct
  for (int i = 0; i < sh.size(); i++)
    CHECK(a->shape[i] == sh[i]);

  // Ensure the values match
  for (int i = 0; i < a->N(); i++) {
    auto *n = dynamic_cast<Number *>(a->values[i]);
    REQUIRE(nullptr != n);
    REQUIRE(ans[i] == doctest::Approx(n->v));
  }
}
