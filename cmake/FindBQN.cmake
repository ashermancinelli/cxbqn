find_program(BQN_EXE "BQN")
if("${BQN_EXE}" STREQUAL "BQN_EXE-NOTFOUND")
  set(HAS_BQN_EXE OFF)
else()
  set(BQN_EXE ${BQN_EXE} CACHE PATH "")
  set(HAS_BQN_EXE ON)
endif()
