add_custom_target(gen_prim_test ALL)

if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Dynamically generating primitive tests")
  set(P_TESTS
    "0≡¯2+2"
    )

  set(GEN_P_TEST_FILE "${PROJECT_BINARY_DIR}/gen-prim-test.sh")
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/prim_tests)
  file(REMOVE ${GEN_P_TEST_FILE})
  file(WRITE ${GEN_P_TEST_FILE} "cd ${CXBQN_EXT_DIR}/cbqn\n")

  set(i 0)
  foreach(P_TEST ${P_TESTS})
    file(
      APPEND ${GEN_P_TEST_FILE}
      "echo -e '/* ${P_TEST} */' > ${PROJECT_BINARY_DIR}/include/prim_tests/t${i}.hpp
${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn '${P_TEST}' >> ${PROJECT_BINARY_DIR}/include/prim_tests/t${i}.hpp\n"
    )
    math(EXPR i "${i} + 1")
  endforeach()

  add_custom_command(
    COMMENT "Generating primitive tests"
    DEPENDS ccxx.bqn
    COMMAND cat ${GEN_P_TEST_FILE}
    OUTPUT ${PROJECT_BINARY_DIR}/include/prim_tests/t0.hpp)
  add_custom_target(
    do_gen_prim_test
    DEPENDS ${PROJECT_BINARY_DIR}/include/prim_tests/t0.hpp
            ccxx.bqn)
else()
  add_custom_target(
    do_gen_prim_test
    COMMAND
      ${CMAKE_COMMAND} -E echo
      "prim tests could not be generated becuase no BQN executable could be found."
  )
endif()

add_dependencies(gen_prim_test do_gen_prim_test)
