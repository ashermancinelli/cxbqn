add_subdirectory(bqn)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(tests
    # test_preruntime test_runtime test_runtime_setprims test_compiler_manual
    test_compiler_setprims test_debug
)
foreach(test ${tests})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl doctest::doctest)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()

set(generatedtests
    test_bc
    test_simple
    # test_prim_l0
    test_prim_setprims_l0
    # test_prim_l1
    test_prim_setprims_l1
    # test_prim_l2
    test_prim_setprims_l2
    # test_prim_l3
    test_prim_setprims_l3
    # test_prim_l4
    test_prim_setprims_l4
    # test_prim_l5
    test_prim_setprims_l5
    # test_prim_l6
    test_prim_setprims_l6
    # test_prim_throws
    test_prim_setprims_throws
    test_under
    test_undo
    test_identity
)

set(FMT_TGT_STR
    "add_custom_target(format-gen-tests COMMENT \"Formatting tests...\""
)
set(INSTALL_TGT_STR
    "add_custom_target(install-tests COMMENT \"Installing tests into source tree...\""
)
foreach(test ${generatedtests})
  if(NOT EXISTS ${test}.cpp)
    file(TOUCH ${test}.cpp)
  endif()
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl doctest::doctest)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
  set(FMT_TGT_STR
      "${FMT_TGT_STR}
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_SOURCE_DIR}/test/${test}.cpp
  "
  )
  set(INSTALL_TGT_STR
      "${INSTALL_TGT_STR}
  COMMAND ${BASH} -c '[ -f ${PROJECT_SOURCE_DIR}/test/${test}.cpp ] && rm ${PROJECT_SOURCE_DIR}/test/${test}.cpp'
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/${test}.cpp ${PROJECT_SOURCE_DIR}/test/${test}.cpp
  "
  )
endforeach()
set(FMT_TGT_STR "${FMT_TGT_STR})")
set(INSTALL_TGT_STR "${INSTALL_TGT_STR})")

string(TIMESTAMP TODAY "%Y%m%d")

if(CXBQN_REGEN_TESTS)

  set(GEN_TGT_STR
      "
  add_custom_target(_gentest COMMENT \"Generating test suite...\"
"
  )

  set(test_generators
      GenPrimL0Tests
      GenPrimL1Tests
      GenPrimL2Tests
      GenPrimL3Tests
      GenPrimL4Tests
      GenPrimL5Tests
      GenPrimL6Tests
      GenPrimThrowsTests
      GenBytecodeTests
      GenSimpleTests
      GenUnderTests
      GenUndoTests
      GenIdentityTests
  )
  foreach(suite ${test_generators})
    set(GEN_TGT_STR
        "${GEN_TGT_STR}
    COMMAND ${CMAKE_COMMAND}
    -DROOT=${PROJECT_SOURCE_DIR}
    -DBQN=${BQN_EXE}
    -DBUILDDIR=${PROJECT_BINARY_DIR}
    -P ${PROJECT_SOURCE_DIR}/cmake/${suite}.cmake
    "
    )
  endforeach()
  set(GEN_TGT_STR "${GEN_TGT_STR})")

  cmake_language(
    EVAL
    CODE
    "
  ${GEN_TGT_STR}
  ${INSTALL_TGT_STR}
  add_dependencies(install-tests _gentest)
  ${FMT_TGT_STR}
  add_dependencies(format-gen-tests install-tests)
  "
  )

  add_custom_target(gentest)
  add_dependencies(gentest install-tests)
  if(NOT ${CLANGFORMAT_EXE} STREQUAL "")
    add_dependencies(gentest format-gen-tests)
  else()
    message(
      WARNING
        "Generated sources will not be formatted, as clang-format could not be found."
    )
  endif()
endif()
