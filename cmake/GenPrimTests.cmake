if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Generating primitive tests")
  set(P_TESTS
    "0≡¯2+2"
    "1e4≡5e3+5e3"
    "'c'≡'a'+2"
    )
  set(P_ANS
    "1"
    "1"
    "1"
    )

  set(P_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim.cpp")
  file(REMOVE ${P_TEST_SOURCE})
  file(WRITE ${P_TEST_SOURCE} "
#include <cxbqn/cxbqn.hpp>
#include \"utils.hpp\"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
")

  foreach(test ans IN ZIP_LISTS P_TESTS P_ANS)
    execute_process(
      COMMAND ${BASH} -c "${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn \"${test}\""
      WORKING_DIRECTORY "${CXBQN_EXT_DIR}/cbqn"
      OUTPUT_VARIABLE compiled_test
      )
    file(APPEND ${P_TEST_SOURCE} "
TEST_CASE(\"${test}\") {
  spdlog::critical(\"test={}, ans={}\", \"${test}\", \"${ans}\");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
    ${compiled_test}
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
")
  endforeach()
else()
  message(WARNING "Attempted to generate primitive tests, but no BQN executable was found.")
endif()
