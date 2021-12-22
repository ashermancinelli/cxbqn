
set(RT_NATIVE_SRC
  replace_with_native.cpp
  r0/self_swap.cpp
  r0/ltack.cpp
  r0/rtack.cpp
  )

add_library(rt_native STATIC ${RT_NATIVE_SRC})
target_link_libraries(rt_native PUBLIC cxbqn::tpl)

add_library(cxbqn::rt_native ALIAS rt_native)
