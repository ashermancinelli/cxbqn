add_subdirectory(spdlog)
add_subdirectory(doctest)
add_subdirectory(utfcpp)
target_include_directories(tpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-subprocess/include)
target_link_libraries(tpl INTERFACE spdlog::spdlog utf8::cpp)

if(CXBQN_EXT_STD_FILESYSTEM)
  add_subdirectory(filesystem)
  target_link_libraries(tpl INTERFACE ghc_filesystem)
endif()

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
else()
  message(STATUS "Found std::span, using builtin")
endif()
