add_subdirectory(spdlog)
add_subdirectory(doctest)
add_subdirectory(utfcpp)
target_include_directories(
  tpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/cpp-subprocess/include
)
target_link_libraries(tpl INTERFACE spdlog::spdlog utf8::cpp)

if(CXBQN_EXT_STD_FILESYSTEM)
  add_subdirectory(filesystem)
  target_link_libraries(tpl INTERFACE ghc_filesystem)
endif()

include(CheckCXXSourceCompiles)
check_cxx_source_compiles(
  "
#include <span>
int main(int argc, char**argv) { return 0; }" HAS_BUILTIN_SPAN
)
if(NOT HAS_BUILTIN_SPAN)
  message(STATUS "Could not compile std::span test, using tpl std::span")
  file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/tcbrindle-span.hpp
       ${PROJECT_BINARY_DIR}/span
  )
else()
  message(STATUS "Found std::span, using builtin")
endif()

file(CREATE_LINK ${CMAKE_CURRENT_SOURCE_DIR}/argparse-4cacdc4.hpp
     ${PROJECT_BINARY_DIR}/argparse.hpp
)

file(GLOB BQN_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/bqn-libs/*.bqn)
install(FILES ${BQN_LIBS} DESTINATION share/bqn)

if(CXBQN_PLOT)
  find_package(
    Python3
    COMPONENTS Interpreter Development
    REQUIRED
  )
  target_link_libraries(
    tpl INTERFACE Python3::Python Python3::Module
  )
  find_package(Python3 COMPONENTS NumPy)
  if(Python3_NumPy_FOUND)
    target_link_libraries(tpl INTERFACE Python3::NumPy)
  else()
    target_compile_definitions(tpl INTERFACE WITHOUT_NUMPY)
  endif()
  target_include_directories(
    tpl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/matplotlib-cpp
  )
endif()
