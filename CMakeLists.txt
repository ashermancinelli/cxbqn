cmake_minimum_required (VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cxbqn LANGUAGES CXX VERSION 0.0.1)

enable_testing()

set(CXBQN_INIT_STACK_SIZE 10000 CACHE STRING "The size the VM stack is initialized with")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(tpl INTERFACE)

find_package(spdlog REQUIRED)

target_link_libraries(tpl INTERFACE spdlog::spdlog)

configure_file(
  include/cxbqn_config.hpp.in
  ${PROJECT_BINARY_DIR}/cxbqn_config.hpp
  )

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
