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
  CompileParams p{
#include <cxbqn/__/compiled_runtime>
  };

  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);

  auto runtime_ret = dynamic_pointer_cast<Array>(ret.v);
  REQUIRE(nullptr != runtime_ret);
  CHECK(runtime_ret->N() == 3);

  auto rt = dynamic_pointer_cast<Array>(runtime_ret->values[0]);
  REQUIRE(nullptr != rt);
  CHECK(rt->N() == 64);

  auto runtime = rt->values;
  CHECK(runtime.size() == 64);

  CompileParams p2{
#include <cxbqn/__/compiled_compiler>
  };

  auto compiler_ret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies);
  REQUIRE(nullptr != compiler_ret.v);
  REQUIRE(nullptr != compiler_ret.scp);
}
