find_package(UnixCommands REQUIRED)
find_program(GIT_EXE "git" CACHE PATH "")
find_program(CLANGFORMAT_EXE "clang-format" CACHE PATH "")
find_program(CMAKEFORMAT_EXE "cmake-format" CACHE PATH "")

add_custom_target(format)

macro(add_format_target)
  set(OPTIONS)
  set(SVARGS REGEX NAME)
  set(MVARGS COMMAND DEPENDS)
  cmake_parse_arguments(
    ADD_FORMAT_TARGET "${OPTIONS}" "${SVARGS}" "${MVARGS}" ${ARGN}
  )
  set(ADD_FORMAT_TARGET_CREATE_TARGET TRUE)
  foreach(COND ${ADD_FORMAT_TARGET_DEPENDS})
    if(NOT EXISTS ${${COND}})
      set(ADD_FORMAT_TARGET_CREATE_TARGET FALSE)
      break()
    endif()
  endforeach()

  if(${ADD_FORMAT_TARGET_CREATE_TARGET})
    execute_process(
      COMMAND ${GIT_EXE} ls-files --cached --exclude-standard
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE ALL_FILES
    )

    string(REPLACE "\n" ";" ALL_FILES "${ALL_FILES}")
    list(FILTER ALL_FILES EXCLUDE REGEX "\\.sh")
    list(FILTER ALL_FILES INCLUDE REGEX "${ADD_FORMAT_TARGET_REGEX}")

    if(EXISTS "${PROJECT_BINARY_DIR}/${ADD_FORMAT_TARGET_NAME}.bash")
      file(REMOVE "${PROJECT_BINARY_DIR}/${ADD_FORMAT_TARGET_NAME}.bash")
    endif()

    list(TRANSFORM ALL_FILES PREPEND "${PROJECT_SOURCE_DIR}/")
    foreach(F ${ALL_FILES})
      if(NOT EXISTS ${F} OR IS_DIRECTORY ${F})
        continue()
      endif()
      string(REPLACE ";" " " ADD_FORMAT_TARGET_COMMAND
                     "${ADD_FORMAT_TARGET_COMMAND}"
      )
      file(APPEND "${PROJECT_BINARY_DIR}/${ADD_FORMAT_TARGET_NAME}.bash"
           "${BASH} -c '${ADD_FORMAT_TARGET_COMMAND} ${F}' &
"
      )
    endforeach()

    file(APPEND "${PROJECT_BINARY_DIR}/${ADD_FORMAT_TARGET_NAME}.bash" "wait
"
    )

    add_custom_target(
      ${ADD_FORMAT_TARGET_NAME}
      COMMAND ${BASH} "${PROJECT_BINARY_DIR}/${ADD_FORMAT_TARGET_NAME}.bash"
      COMMENT "Running format target '${ADD_FORMAT_TARGET_NAME}'..."
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
  else()
    add_custom_target(
      ${ADD_FORMAT_TARGET_NAME}
      COMMAND
        ${CMAKE_COMMAND} -E echo
        "Target '${ADD_FORMAT_TARGET_NAME}' cannot run because '${ADD_FORMAT_TARGET_DEPENDS}' was false."
    )
  endif()
  add_dependencies(format ${ADD_FORMAT_TARGET_NAME})
endmacro()

add_format_target(
  NAME
  clang-format
  REGEX
  "\\.c$|\\.cpp$|\\.cu$|\\.h$|\\.hpp$"
  COMMAND
  ${CLANGFORMAT_EXE}
  -i
  DEPENDS
  CLANGFORMAT_EXE
)

add_format_target(
  NAME
  cmake-format
  REGEX
  "CMakeLists.txt$|\\.cmake$"
  COMMAND
  ${CMAKEFORMAT_EXE}
  -i
  DEPENDS
  CMAKEFORMAT_EXE
)
