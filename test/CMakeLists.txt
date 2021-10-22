
foreach(test test_vm test_op)
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn)
  add_test(
    NAME ${test}
    COMMAND $<TARGET_FILE:${test}>
    )
endforeach()
