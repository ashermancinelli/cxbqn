add_library(_cxbqn vm.cpp types.cpp provides.cpp)
target_link_libraries(_cxbqn PUBLIC tpl)
add_library(cxbqn::cxbqn ALIAS _cxbqn)

add_executable(cxbqn_driver driver.cpp)
target_link_libraries(cxbqn_driver PUBLIC cxbqn::cxbqn)
set_target_properties(
  cxbqn_driver
  PROPERTIES
  OUTPUT_NAME
  "cxbqn"
  )
