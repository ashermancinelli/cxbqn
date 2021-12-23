cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  cxbqn
  LANGUAGES CXX C
  VERSION 0.10.1
)

set(CXBQN_INIT_STACK_SIZE
    10000
    CACHE STRING "The size the VM stack is initialized with"
)

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "NVHPC")
  set(CMAKE_CXX_FLAGS
      "-Wall -Wextra ${CMAKE_CXX_FLAGS}"
      CACHE STRING ""
  )
endif()

set(CXBQN_EXT_STD_FILESYSTEM
    OFF
    CACHE BOOL "Build std::filesystem using git submodule"
)
set(CXBQN_BUILD_TOOLS
    OFF
    CACHE BOOL "Build extra tools, eg the compiler examiner"
)
set(CXBQN_BUILD_TESTS
    OFF
    CACHE BOOL "Build tests, add CTest support"
)
set(CXBQN_REGEN_TESTS
    OFF
    CACHE BOOL "Regenerate bytecode, simple, and primitive tests"
)
set(CXBQN_MEM_STRATEGY
    "leak"
    CACHE STRING
          "Select memory management strategy from 'shared_ptr', 'gc', 'leak'"
)
set(CXBQN_STACKTRACE
    OFF
    CACHE
      BOOL
      "Runs every VM invocation in a try-catch block to provide stack trace information"
)
set(CXBQN_STACKTRACE_DEEP
    OFF
    CACHE
      BOOL
      "Checks many additional calls for failure to provide more detailed stack trace information"
)
set(CXBQN_GEN_CODECOV
    OFF
    CACHE BOOL "Generate code coverage data. Build type must be debug."
)
set(CXBQN_PROFILE_STARTUP
    OFF
    CACHE BOOL "Output profiling information from the driver"
)
set(CXBQN_PROFILE_VM
    OFF
    CACHE BOOL "Output profiling information from the VM"
)
set(CXBQN_DEBUG_VM
    OFF
    CACHE BOOL "Verbose output in the VM for debugging"
)
set(CXBQN_DEBUG_VM_FILE
    ""
    CACHE STRING "Redirect debugging output from VM to a file."
)
set(CXBQN_DEBUG_VMSTACK
    OFF
    CACHE BOOL "Display the entire stack in the VM for debugging"
)
set(CXBQN_DEEPCHECKS
    ON
    CACHE BOOL "Deep null checking and debugging information"
)
set(CXBQN_READLINE
    OFF
    CACHE BOOL "Use libreadline for BQN REPL"
)
set(CXBQN_COLOR
    OFF
    CACHE BOOL "Output VM information in color"
)
set(CXBQN_LOG
    OFF
    CACHE BOOL "Enable logging in CXBQN"
)
set(CXBQN_LOGLEVEL
    "level::off"
    CACHE STRING "Log level spdlog will be set to"
)
set(CHECK_SUBMODULES
    ON
    CACHE BOOL "Check git submodules on every build"
)
set(CXBQN_CUDA
    OFF
    CACHE BOOL "Enable CUDA acceleration and non-standard builtins"
)
set(CXBQN_FFI
    OFF
    CACHE BOOL "Enable foreign function interface"
)
set(CXBQN_NATIVE_R0
  ON
  CACHE BOOL "Enable native C++ functions for lower-level runtime"
  )
set(CXBQN_NATIVE_R1
  OFF
  CACHE BOOL "Enable native C++ functions for higher-level runtime"
  )

add_definitions("-DCXBQN_MEM_${CXBQN_MEM_STRATEGY}=1")

if("${CXBQN_DEBUG_VM_FILE}" STREQUAL "stdout")
  set(CXBQN_DEBUG_VM_USE_FILE
      ON
      CACHE BOOL ""
  )
else()
  set(CXBQN_DEBUG_VM_USE_FILE
      OFF
      CACHE BOOL ""
  )
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING ""
  )
endif()

set(HAS_BQN_EXE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXBQN_EXT_DIR ${PROJECT_SOURCE_DIR}/ext/)
include(CMakePrintHelpers)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(tpl INTERFACE)
add_library(cxbqn::tpl ALIAS tpl)

if(CXBQN_READLINE)
  find_package(Readline)
  target_link_libraries(tpl INTERFACE ${Readline_LIBRARY})
  target_include_directories(tpl INTERFACE ${Readline_INCLUDE_DIR})
endif()

if(${CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT})
  message(STATUS "Found default install prefix, setting to ${PROJECT_BINARY_DIR}/install")
  set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
endif()

find_package(UnixCommands REQUIRED)
include(cmake/Linters.cmake)
include(cmake/CheckGitSubmodules.cmake)
include(cmake/FindBQN.cmake)
include(cmake/CodeCoverage.cmake)

if(CXBQN_CUDA)
  if("${CMAKE_CUDA_ARCHITECTURES}" STREQUAL "")
    set(CMAKE_CUDA_ARCHITECTURES 60)
  endif()

  set(CMAKE_CUDA_FLAGS
      "${CMAKE_CUDA_FLAGS} --extended-lambda --expt-relaxed-constexpr"
  )

  include(CheckLanguage)
  check_language(CUDA)
  enable_language(CUDA)
endif()

if(CXBQN_FFI)
  message(STATUS "Enabling foreign function interface")
  target_link_libraries(tpl INTERFACE ${CMAKE_DL_LIBS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(ext)

configure_file(
  include/cxbqn/config.hpp.in ${PROJECT_BINARY_DIR}/include/cxbqn/config.hpp
)

add_subdirectory(src)

if(CXBQN_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

file(GLOB_RECURSE CXBQN_HEADERS include/cxbqn/*.hpp)
install(FILES ${CXBQN_HEADERS} DESTINATION include/cxbqn)
