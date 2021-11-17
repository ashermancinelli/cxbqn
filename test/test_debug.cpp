#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("'a'≡⟨⟩⊑'a'") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical("test='{}'", "⟨7,7‿7,7⟩≡⟨⟨⟩,⟨⟨⟩,⟨⟩⟩,⟨⟩⟩⊑<7");
  CompileParams p(
      {0,3,0,0,16,0,2,11,0,11,0,11,0,11,2,11,0,11,3,17,0,1,0,3,0,3,0,3,11,2,0,3,11,3,17,7},
{runtime[12],runtime[18],runtime[37],7},
{{0,1,0}},
{{0,0}},
{{27,27,26,26,26,25,25,11,11,15,15,18,18,14,14,22,22,10,10,25,9,9,1,1,3,3,5,5,5,5,7,7,0,0,9,0},{27,27,26,26,26,25,25,12,12,16,16,19,19,20,20,23,23,24,24,25,9,9,1,1,3,3,5,5,5,5,7,7,8,8,9,8}},
std::make_shared<Array>(U"⟨7,7‿7,7⟩≡⟨⟨⟩,⟨⟨⟩,⟨⟩⟩,⟨⟩⟩⊑<7")
      );
  fmt::print("startingtest\n");
  spdlog::critical("startingtest");
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
