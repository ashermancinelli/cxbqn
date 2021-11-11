#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Test Simplified _isGlyph") {
  spdlog::critical("test '{}'", "(×`\"+-×÷∾≍\"(1-=)⌜{⟨⟩⥊⟨𝕩⟩}) '∾'");
  const auto runtime = provides::get_runtime_bionly()->values;
  CompileParams p{{0,  7,  1, 1, 0,  4, 0, 2, 0,  0,  0,  6,
                   21, 26, 0, 8, 21, 0, 5, 0, 1,  26, 20, 16,
                   7,  34, 0, 1, 11, 1, 0, 3, 11, 0,  17, 7},
                  {runtime[1], runtime[2], runtime[15], runtime[22],
                   runtime[47], runtime[51], 1, make_shared<Character>(U'∾'),
                   make_shared<Array>(U"+-×÷∾≍")},
                  {{0, 1, 0}, {0, 0, 1}},
                  {{0, 0}, {25, 3}}};

  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto ar = dynamic_pointer_cast<Array>(ret.v);
  REQUIRE(nullptr != ar);
  REQUIRE(ar->N() == 6);
  std::vector<int> ans{1, 1, 1, 1, 0, 0};
  for (int i = 0; i < ans.size(); i++)
    REQUIRE(ans[i] ==
            doctest::Approx(dynamic_pointer_cast<Number>(ar->values[i])->v));
}

TEST_CASE("Check Fold Impl") {
  spdlog::critical("test '{}'",
                   "{ l←5 ⋄ r←l⊑𝕩 ⋄ 𝕩{r↩(((l-1)-𝕩)⊑𝕗)+r}⌜↕l ⋄ r } 1‿1‿1‿1‿0‿0");
  const auto runtime = provides::get_runtime_bionly()->values;
  CompileParams p{
      {0, 6,  0, 6,  0,  6, 0,  6,  0,  7,  0,  7,  11, 6,  1,  1,  16, 7, 0,
       5, 33, 0, 3,  48, 6, 32, 0,  1,  0,  3,  32, 0,  3,  17, 33, 0,  4, 48,
       6, 32, 0, 3,  0,  2, 16, 0,  4,  1,  2,  34, 0,  1,  26, 26, 16, 6, 32,
       0, 4,  7, 32, 1,  4, 0,  0,  34, 0,  4,  0,  3,  34, 0,  1,  0,  1, 0,
       6, 0,  1, 32, 1,  3, 17, 17, 17, 17, 33, 1,  4,  49, 7},
      {runtime[0], runtime[1], runtime[27], runtime[36], runtime[47], 5, 1, 0},
      {{0, 1, 0}, {0, 0, 1}, {1, 0, 2}},
      {{0, 0}, {18, 5}, {60, 5}}};
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  REQUIRE(4 == doctest::Approx(n->v));
}
