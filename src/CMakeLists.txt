add_library(cxbqn vm.cpp value_types.cpp)
target_link_libraries(cxbqn PUBLIC tpl)
add_library(cxbqn::cxbqn ALIAS cxbqn)
