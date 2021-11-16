#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Evaluate Compiler After SetPrims") {
  auto runtime = provides::get_runtime_setprims_annot()->values;

  CompileParams p(
#include <cxbqn/__/compiled_compiler_annot>
  );

  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies,
                     p.source_indices.value(), p.source_str);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
}
