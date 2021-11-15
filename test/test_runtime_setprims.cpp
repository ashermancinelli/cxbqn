#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;


TEST_CASE("Evaluate Runtime and call SetPrims") {
  const auto provide = provides::get_provides()->values;

  static CompileParams p{
#include <cxbqn/__/compiled_runtime>
  };

  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

  auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);
  auto runtime = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

  auto setprims = runtime_ret->values[1];

  auto decompose = make_shared<Decompose>(runtime);
  auto primind = make_shared<PrimInd>(runtime);

  setprims->call(1, {setprims, O<Value>(new Array({decompose, primind}))});
}
