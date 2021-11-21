add_test(
  NAME "BQN Syntax"
  COMMAND $<TARGET_FILE:BQN> -f test/bqn/syntax.bqn
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
