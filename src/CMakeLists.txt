add_library(
  cxbqn

  # Top level definitions for basic types, mostly defined in types.hpp
  bi.cpp
  vm.cpp
  types.cpp
  array.cpp
  block.cpp
  blockdef.cpp
  blockinst.cpp
  scope.cpp
  op.cpp
  instructions.cpp

  # System functions, eg •Open
  sys/open.cpp
  sys/rename.cpp
  sys/repr.cpp
  sys/sys_helper.cpp
  sys/sys_function_resolver.cpp

  # Builtin functions/modifiers
  builtin/stile.cpp
  builtin/root.cpp
  builtin/assert.cpp
  builtin/le.cpp
  builtin/type.cpp
  builtin/fne.cpp
  builtin/floor.cpp
  builtin/table.cpp
  builtin/arraydepth.cpp
  builtin/range.cpp
  builtin/shape.cpp
  builtin/scan.cpp
  builtin/fmtnum.cpp
  builtin/glyph.cpp
  builtin/grouplen.cpp
  builtin/groupord.cpp
  builtin/primind.cpp
  builtin/power.cpp
  builtin/provides_helpers.cpp
  builtin/mul.cpp
  builtin/minus.cpp
  builtin/arith.cpp
  builtin/catch.cpp
  builtin/decompose.cpp
  builtin/deshape.cpp
  builtin/div.cpp
  builtin/eq.cpp
  builtin/feq.cpp
  builtin/fillby.cpp
  builtin/pick.cpp
  builtin/plus.cpp
  builtin/valence.cpp
)
target_link_libraries(cxbqn PUBLIC tpl)
add_library(cxbqn::cxbqn ALIAS cxbqn)

add_executable(driver driver.cpp)
target_link_libraries(driver PUBLIC cxbqn::cxbqn)
set_target_properties(driver PROPERTIES OUTPUT_NAME "cxbqn")

add_custom_command(
  TARGET driver
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:driver>"
          "${PROJECT_BINARY_DIR}/BQN"
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:driver>"
          "${PROJECT_BINARY_DIR}/BQN-cxbqn"
)
