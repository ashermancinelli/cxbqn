
foreach(test test_vm test_op test_values)
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PUBLIC cxbqn::cxbqn cxbqn::tpl)
  add_test(
    NAME ${test}
    COMMAND $<TARGET_FILE:${test}>
    )
endforeach()
