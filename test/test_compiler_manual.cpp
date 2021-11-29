#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Evaluate Compiler") {
  const auto _provide = provides::get_provides();
  const auto provide = _provide->values;
  auto rcu =
#include <cxbqn/__/r>
  };

  auto ret = vm::run(rcu);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);

  auto runtime_ret = dyncast<Array>(ret.v);
  REQUIRE(nullptr != runtime_ret);
  CHECK(runtime_ret->N() == 3);

  auto rt = dyncast<Array>(runtime_ret->values[0]);
  REQUIRE(nullptr != rt);
  CHECK(rt->N() == 64);

  auto runtime = rt->values;
  CHECK(runtime.size() == 64);

  auto ccu =
#include <cxbqn/__/c>
  ;

  auto compiler_ret = vm::run(ccu);
  REQUIRE(nullptr != compiler_ret.v);
  REQUIRE(nullptr != compiler_ret.scp);
}
