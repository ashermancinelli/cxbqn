#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("2≡⊑2") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "2≡⊑2");
  CompileParams p(
      {0, 2, 0, 1, 16, 0, 0, 0, 2, 17, 7}, {runtime[18], runtime[37], 2},
      {{0, 1, 0}}, {{0, 0}},
      {{3, 3, 2, 2, 2, 1, 1, 0, 0, 1, 0}, {3, 3, 2, 2, 2, 1, 1, 0, 0, 1, 0}},
      std::make_shared<Array>(U"2≡⊑2"));
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
