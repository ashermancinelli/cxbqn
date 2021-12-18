find_program(BQN_EXE "BQN")
if("${BQN_EXE}" STREQUAL "BQN_EXE-NOTFOUND")
  find_program(MAKE "make")
  if(NOT MAKE)
    message(FATAL_ERROR "CXBQN requires GNU make if no BQN executable is provided.")
  endif()
  message(STATUS "Could not find BQN executable. Building CBQN from source.")
  execute_process(
    COMMAND ${MAKE} CC=${CMAKE_C_COMPILER}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/ext/cbqn
    )
  set(BQN_EXE ${PROJECT_SOURCE_DIR}/ext/cbqn/BQN CACHE PATH "")
  message(STATUS "BQN executable: ${BQN_EXE}")
  set(HAS_BQN_EXE ON)
else()
  set(BQN_EXE ${BQN_EXE} CACHE PATH "")
  set(HAS_BQN_EXE ON)
endif()
