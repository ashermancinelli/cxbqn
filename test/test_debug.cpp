#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("0≡{_op←{𝕗}⋄op='o'}") {
  const auto provide = provides::get_provides()->values;
  static CompileParams p{
#include <cxbqn/__/compiled_runtime>
  };
  auto rtret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

  // Decompose the result to get the array with just the runtime
  auto runtime_ret = std::dynamic_pointer_cast<Array>(rtret.v);
  auto runtime_raw = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

  auto setprims = runtime_ret->values[1];

  // Inform the two latter builtins of the runtime so they can refer to it
  auto decompose = make_shared<Decompose>(runtime_raw);
  auto primind = make_shared<PrimInd>(runtime_raw);

  setprims->call(1, {setprims, O<Array>(new Array({decompose, primind}))});

  const auto runtime = runtime_raw->values;
  // const auto runtime = provides::get_runtime_bionly()->values;

  spdlog::critical("test='{}'", "0≡{_op←{𝕗}⋄op='o'}");
  CompileParams p2{
      {1, 1, 0, 1, 0, 2,  17, 7, 1,  2, 33, 0, 0, 48,
       6, 0, 3, 0, 0, 34, 0,  0, 17, 7, 34, 0, 1, 7},
      {runtime[15], runtime[18], 0, std::make_shared<Character>(U'o')},
      {{0, 1, 0}, {0, 1, 1}, {1, 1, 2}},
      {{0, 0}, {8, 1}, {24, 2}}};
  auto ret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1 == doctest::Approx(n->v));
}
