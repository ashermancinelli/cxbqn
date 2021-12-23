set(RT_NATIVE_SRC
    # Sets runtime elements with native versions. See src/driver/main.cpp
    replace_with_native.cpp

    # Replacements for r0
    r0/self_swap.cpp
    r0/ltack.cpp
    r0/rtack.cpp
    r0/ne.cpp
    r0/join_to.cpp
    r0/enlist_pair.cpp
    r0/each.cpp
    r0/take.cpp
    r0/drop.cpp
    r0/constant.cpp
    r0/choose.cpp
    r0/atop.cpp
    r0/over.cpp
    r0/fold.cpp
    r0/before.cpp
    r0/after.cpp
    r0/repeat.cpp
    r0/less.cpp

    # Currently no replacements for r1
)

add_library(rt_native STATIC ${RT_NATIVE_SRC})
target_link_libraries(rt_native PUBLIC cxbqn::tpl)

add_library(cxbqn::rt_native ALIAS rt_native)
