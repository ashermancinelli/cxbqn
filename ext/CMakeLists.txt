add_subdirectory(catch)

find_package(spdlog QUIET)
if(NOT TARGET spdlog::spdlog)
  message(STATUS "Cant find external spdlog, building it as a subproject")
  add_subdirectory(spdlog)
endif()
target_link_libraries(tpl INTERFACE spdlog::spdlog)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
#include <span>
int main(int argc, char**argv) { return 0; }" HAS_BUILTIN_SPAN)
if(NOT HAS_BUILTIN_SPAN)
  message(STATUS "Could not compile std::span test, using tpl std::span")
  add_subdirectory(span)
  file(CREATE_LINK
    ${CMAKE_CURRENT_SOURCE_DIR}/span/include/tcb/span.hpp
    ${PROJECT_BINARY_DIR}/span
    )
endif()
target_link_libraries(tpl INTERFACE span)
