find_program(BQN_EXE "BQN")
if(NOT BQN_EXE)
  message(STATUS "No BQN executable could be found.")
  set(HAS_BQN_EXE OFF)
else()
  message(STATUS "BQN executable: ${BQN_EXE}")
  set(HAS_BQN_EXE ON)
endif()
