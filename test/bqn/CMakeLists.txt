set(BQN_TESTS
  syntax.bqn
  )

if(CXBQN_CUDA)
  list(APPEND BQN_TESTS cuda.bqn)
endif()

add_test(
  NAME "BQN-Test-Suite"
  COMMAND $<TARGET_FILE:BQN> -f test/bqn/runner.bqn ${BQN_TESTS}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

add_library(userfn SHARED ffitest.cpp)
target_link_libraries(userfn PRIVATE cxbqn::cxbqn)
