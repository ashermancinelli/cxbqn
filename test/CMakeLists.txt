include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(tests
    test_bc
    test_prim
    test_simple
)

foreach(test ${tests})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl doctest::doctest)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()

if(CXBQN_REGEN_TESTS)
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
