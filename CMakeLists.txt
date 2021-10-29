cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  cxbqn
  LANGUAGES CXX
  VERSION 0.0.1)

enable_testing()

set(CXBQN_INIT_STACK_SIZE
    10000
    CACHE STRING "The size the VM stack is initialized with")

set(CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}" CACHE STRING "")

set(CXBQN_DEEPCHECKS ON CACHE BOOL "Deep null checking and debugging information")
set(CHECK_SUBMODULES ON CACHE BOOL "Check git submodules on every build")
set(HAS_BQN_EXE OFF)
set(CXBQN_EXT_DIR ${PROJECT_SOURCE_DIR}/ext/)
include(CMakePrintHelpers)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(tpl INTERFACE)
add_library(cxbqn::tpl ALIAS tpl)

include(cmake/Linters.cmake)
include(cmake/CheckGitSubmodules.cmake)
include(cmake/FindBQN.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(ext)

configure_file(include/cxbqn/config.hpp.in ${PROJECT_BINARY_DIR}/include/cxbqn/config.hpp)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
