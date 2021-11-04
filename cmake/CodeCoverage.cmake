if(CXBQN_GEN_CODECOV)
  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      message(STATUS "Adding code coverage support")
      set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
      find_program(GCOVR "gcovr")
      if(${GCOVR} STREQUAL "GCOVR-NOTFOUND")
        message(FATAL_ERROR "")
      endif()
      file(TOUCH ${PROJECT_BINARY_DIR}/cov.html ${PROJECT_BINARY_DIR}/cov.txt)
      add_custom_target(
        cov
        COMMENT "Generating code coverage data..."
        COMMAND ${BASH} -c '${GCOVR} -r ${PROJECT_SOURCE_DIR} --html > ${PROJECT_BINARY_DIR}/cov.html'
        COMMAND ${BASH} -c '${GCOVR} -r ${PROJECT_SOURCE_DIR} --txt > cov.txt'
        COMMAND ${CMAKE_COMMAND} -E echo "Done generating code coverage data. See cov.html and cov.txt."
        )
    else()
      message(
        FATAL_ERROR
        "To generate code coverage info, must use GCC and Debug mode.")
  endif()
else()
  add_custom_target(
    cov
    COMMAND ${CMAKE_COMMAND} -E false
    COMMENT "Cannot generate code coverage data. Enable cmake option CXBQN_GEN_CODECOV."
    )
endif()
