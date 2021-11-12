include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(tests
    test_bc
    test_prim
    test_simple
    test_bi
    test_provide
    test_preruntime
    test_runtime
    test_debug
)

foreach(test ${tests})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl doctest::doctest)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()

file(REMOVE ${PROJECT_BINARY_DIR}/bcgen.sh)
file(WRITE ${PROJECT_BINARY_DIR}/bcgen.sh "
cd ${PROJECT_SOURCE_DIR}/ext/cbqn && ${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${PROJECT_SOURCE_DIR}/ext//bqn \"$@\"
")

if(CXBQN_REGEN_TESTS)
  include(GenHelpers)
  include(GenBytecodeTests)
  include(GenPrimTests)
  include(GenSimpleTests)
  add_custom_target(format-gen-tests
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_bc.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_prim.cpp
    COMMAND ${CLANGFORMAT_EXE} -i ${PROJECT_BINARY_DIR}/test_simple.cpp
    COMMENT "Formatting generated sources..."
    )
  add_custom_target(gentest
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_bc.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_prim.cpp
    COMMAND ${CMAKE_COMMAND} -E rm ${CMAKE_CURRENT_SOURCE_DIR}/test_simple.cpp
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_bc.cpp ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_prim.cpp ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/test_simple.cpp ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Installing generated sources into the source tree..."
    )
  if(NOT ${CLANGFORMAT_EXE} STREQUAL "")
    add_dependencies(gentest format-gen-tests)
  else()
    message(WARNING "Generated sources will not be formatted, as clang-format could not be found.")
  endif()
endif()
