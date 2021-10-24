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

set(CHECK_SUBMODULES ON CACHE BOOL "Check git submodules on every build")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(tpl INTERFACE)
add_library(cxbqn::tpl ALIAS tpl)

include(cmake/Linters.cmake)
include(cmake/CheckGitSubmodules.cmake)
include(cmake/FindBQN.cmake)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(ext)

configure_file(include/cxbqn_config.hpp.in
               ${PROJECT_BINARY_DIR}/cxbqn_config.hpp)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
