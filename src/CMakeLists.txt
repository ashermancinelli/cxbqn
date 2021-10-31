add_library(cxbqn
  vm.cpp
  types.cpp
  # provides.cpp
  op.cpp
  instructions0.cpp
  instructions1.cpp
  debug.cpp
  )
target_link_libraries(cxbqn PUBLIC tpl)
add_library(cxbqn::cxbqn ALIAS cxbqn)

#add_executable(cxbqn_driver driver.cpp)
#target_link_libraries(cxbqn_driver PUBLIC cxbqn::cxbqn)
#set_target_properties(
#  cxbqn_driver
#  PROPERTIES
#  OUTPUT_NAME
#  "cxbqn"
#  )
