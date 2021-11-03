add_custom_target(gen_bc_test ALL)

if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Dynamically generating newest bytecode tests")
  file(
    STRINGS ${CXBQN_EXT_DIR}/bqn/test/cases/bytecode.bqn BC_TESTS
    REGEX "%"
    ENCODING "UTF-8")
  list(TRANSFORM BC_TESTS REPLACE "^([0-9]+)[ ]+%" "")

  set(GEN_BC_TEST_FILE "${PROJECT_BINARY_DIR}/gen-bc-test.sh")
  set(ALL_BC_TESTS_HPP "${PROJECT_BINARY_DIR}/include/bc_tests/all.hpp")
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/bc_tests)
  file(REMOVE ${GEN_BC_TEST_FILE})
  file(REMOVE ${ALL_BC_TESTS_HPP})
  file(WRITE ${GEN_BC_TEST_FILE} "cd ${CXBQN_EXT_DIR}/cbqn\n")

  set(i 0)
  foreach(BC_TEST ${BC_TESTS})
    file(
      APPEND ${GEN_BC_TEST_FILE}
      "echo -e '/* ${BC_TEST} */' > ${PROJECT_BINARY_DIR}/include/bc_tests/t${i}.hpp
${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn '${BC_TEST}' >> ${PROJECT_BINARY_DIR}/include/bc_tests/t${i}.hpp\n"
    )
    file(APPEND ${ALL_BC_TESTS_HPP}
         "CompileParams t${i}{\n#include <bc_tests/t${i}.hpp>\n};\n")
    math(EXPR i "${i} + 1")
  endforeach()
  file(APPEND ${ALL_BC_TESTS_HPP} "#define CXBQN_NUM_BC_TESTS ${i}\n")

  add_custom_command(
    COMMENT "Dynamically generating newest bytecode tests"
    DEPENDS ccxx.bqn
    COMMAND ${BASH} ${GEN_BC_TEST_FILE}
    OUTPUT ${ALL_BC_TESTS_HPP} ${PROJECT_BINARY_DIR}/include/bc_tests/t0.hpp)
  add_custom_target(
    do_gen_bc_test
    DEPENDS ${ALL_BC_TESTS_HPP} ${PROJECT_BINARY_DIR}/include/bc_tests/t0.hpp
            ccxx.bqn)
else()
  add_custom_target(
    do_gen_bc_test
    COMMAND
      ${CMAKE_COMMAND} -E echo
      "Newest bytecode tests could not be generated becuase no BQN executable could be found."
  )
endif()

add_dependencies(gen_bc_test do_gen_bc_test)
