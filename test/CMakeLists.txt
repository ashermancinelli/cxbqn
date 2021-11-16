include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(tests
    test_bc
    test_bi
    test_simple
    # test_prim_l0
    test_prim_setprims_l0
    # test_prim_l1
    test_prim_setprims_l1
    # test_prim_l2
    test_prim_setprims_l2
    # test_prim_l3
    test_prim_setprims_l3
    # test_preruntime
    # test_runtime
    # test_runtime_setprims
    # test_compiler_manual
    test_compiler_setprims
    test_debug
)

foreach(test ${tests})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl doctest::doctest)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()

file(REMOVE ${PROJECT_BINARY_DIR}/bcgen.sh)
file(
  WRITE ${PROJECT_BINARY_DIR}/ccxx-wrapper.sh
  "
cd ${PROJECT_SOURCE_DIR}/ext/cbqn && ${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${PROJECT_SOURCE_DIR}/ext//bqn \"$@\"
"
)
execute_process(
  COMMAND ${BASH} -c "chmod +x ccxx-wrapper.sh"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

if(CXBQN_REGEN_TESTS)
  include(GenHelpers)
  include(GenBytecodeTests)
  include(GenPrimL0Tests)
  include(GenPrimL1Tests)
  include(GenPrimL2Tests)
  include(GenPrimL3Tests)
  include(GenSimpleTests)
  add_custom_target(
    format-gen-tests
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_bc.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_prim_l0.cpp
    COMMAND ${CLANGFORMAT_EXE} -i
            ${PROJECT_BINARY_DIR}/test_prim_setprims_l0.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_prim_l1.cpp
    COMMAND ${CLANGFORMAT_EXE} -i
            ${PROJECT_BINARY_DIR}/test_prim_setprims_l1.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_prim_l2.cpp
    COMMAND ${CLANGFORMAT_EXE} -i
            ${PROJECT_BINARY_DIR}/test_prim_setprims_l2.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_prim_l3.cpp
    COMMAND ${CLANGFORMAT_EXE} -i
            ${PROJECT_BINARY_DIR}/test_prim_setprims_l3.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_simple.cpp
    COMMENT "Formatting generated sources..."
  )
  add_custom_target(
    gentest
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_bc.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_l0.cpp
    COMMAND ${CMAKE_COMMAND} -E rm
            ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_setprims_l0.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_l1.cpp
    COMMAND ${CMAKE_COMMAND} -E rm
            ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_setprims_l1.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_l2.cpp
    COMMAND ${CMAKE_COMMAND} -E rm
            ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_setprims_l2.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_l3.cpp
    COMMAND ${CMAKE_COMMAND} -E rm
            ${CMAKE_CURRENT_SOURCE_DIR}/test_prim_setprims_l3.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_simple.cpp
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_bc.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_l0.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
      ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_setprims_l0.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_l1.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
      ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_setprims_l1.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_l2.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
      ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_setprims_l2.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_l3.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
      ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim_setprims_l3.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_simple.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Installing generated sources into the source tree..."
  )
  if(NOT ${CLANGFORMAT_EXE} STREQUAL "")
    add_dependencies(gentest format-gen-tests)
  else()
    message(
      WARNING
        "Generated sources will not be formatted, as clang-format could not be found."
    )
  endif()
endif()
