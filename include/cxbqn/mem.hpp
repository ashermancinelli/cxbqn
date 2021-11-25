#pragma once
#include <type_traits>
#include <memory>

namespace cxbqn::types {

#define CXBQN_MEM_SHAREDPTR 1

#ifdef CXBQN_MEM_SHAREDPTR // Use shared ptrs to manage memory

// "Owned Value"
template <typename T> using O = std::shared_ptr<T>;

// "Weak/Unowned Value"
template <typename T> using W = std::weak_ptr<T>;

template <typename T, typename F> auto dyncast(O<F> f) {
  return std::dynamic_pointer_cast<T>(f);
}

#define CXBQN_NEW(Type, ...) std::make_shared<Type>(__VA_ARGS__)

#elif CXBQN_MEM_GC // Use mark/sweep
#error "unsupported"
#elif CXBQN_MEM_LEAK // Leak everything

template <typename T> using O = std::add_pointer<T>;
template <typename T> using W = std::add_pointer<T>;
template <typename T, typename F> auto dyncast(O<F> f) {
  return dynamic_cast<T>(f);
}
#define CXBQN_NEW(Type, ...) new Type(__VA_ARGS__)

#else
#error "unsupported"
#endif

using std::make_shared;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::shared_ptr;
using std::weak_ptr;

}
