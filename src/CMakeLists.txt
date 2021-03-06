set(CXBQN_SRC

  # Top level definitions for basic types, mostly defined in types.hpp
  types/array_utils.cpp
  types/ref_array.cpp
  types/bi.cpp
  types/mem.cpp
  types/varalias.cpp
  types/namespace.cpp
  types/vm.cpp
  types/types.cpp
  types/array.cpp
  types/block.cpp
  types/blockdef.cpp
  types/blockinst.cpp
  types/scope.cpp
  types/op.cpp
  types/run.cpp

  # Implementation of instructions
  instructions/set_.cpp
  instructions/alim.cpp
  instructions/varm.cpp
  instructions/varo.cpp
  instructions/fn1c.cpp
  instructions/fn1o.cpp
  instructions/pred.cpp
  instructions/seth.cpp
  instructions/vfym.cpp
  instructions/notm.cpp
  instructions/fldo.cpp
  instructions/fldm.cpp
  instructions/fn2c.cpp
  instructions/fn2o.cpp
  instructions/dfnd.cpp
  instructions/arro.cpp
  instructions/arrm.cpp
  instructions/md1c.cpp
  instructions/md2c.cpp
  instructions/tr2d.cpp
  instructions/tr3d.cpp
  instructions/tr3o.cpp

  # System functions, eg •Open
  sys/open.cpp
  sys/list.cpp
  sys/sh.cpp
  sys/exit.cpp
  sys/bqn.cpp
  sys/out.cpp
  sys/import.cpp
  sys/flines.cpp
  sys/unixtime.cpp
  sys/timed.cpp
  sys/show.cpp
  sys/rename.cpp
  sys/repr.cpp
  sys/sys_helper.cpp
  sys/sys_function_resolver.cpp
  $<$<BOOL:${CXBQN_CUDA}>:sys/cudafor.cu>
  $<$<BOOL:${CXBQN_FFI}>:sys/ffi.cpp>

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

  namespaces/file.cpp
  namespaces/cxbqn.cpp
  namespaces/std.cpp
  $<$<BOOL:${CXBQN_PLOT}>:namespaces/cxbqn/plot.cpp>
  )

add_library(
  cxbqn
  ${CXBQN_SRC}
)
target_link_libraries(cxbqn PUBLIC tpl)
install(TARGETS cxbqn DESTINATION lib)
add_library(cxbqn::cxbqn ALIAS cxbqn)

# The native runtime library is only needed for the driver
add_subdirectory(rt_native)

add_executable(BQN driver/driver.cpp driver/main.cpp)
target_link_libraries(BQN PUBLIC cxbqn::cxbqn cxbqn::tpl cxbqn::rt_native)
install(TARGETS BQN DESTINATION bin)

add_custom_command(
  TARGET BQN
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:BQN>"
          ${PROJECT_BINARY_DIR}
          )

add_subdirectory(tools)
