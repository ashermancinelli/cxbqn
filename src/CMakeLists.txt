add_library(
  cxbqn
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

  builtin/assert.cpp
  builtin/le.cpp
  builtin/type.cpp
  builtin/fne.cpp
  builtin/table.cpp
  builtin/arraydepth.cpp
  builtin/range.cpp
  builtin/shape.cpp
  builtin/scan.cpp
  builtin/grouplen.cpp
  builtin/groupord.cpp
  builtin/primind.cpp
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

# add_executable(cxbqn_driver driver.cpp) target_link_libraries(cxbqn_driver
# PUBLIC cxbqn::cxbqn) set_target_properties( cxbqn_driver PROPERTIES
# OUTPUT_NAME "cxbqn" )
