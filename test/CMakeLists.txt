include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(tests
    test_bc
    test_prim
)

foreach(test ${tests})
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl Catch2::Catch2)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach()

include(GenBytecodeTests)
add_dependencies(test_bc gen_bc_test)

include(GenPrimTests)
add_dependencies(test_prim gen_prim_test)
