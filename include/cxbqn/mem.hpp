#pragma once
#include <experimental/memory>
#include <type_traits>

namespace cxbqn::types {

// Just a dummy for GC'ing allocations at some point
struct Marked {
  Marked() {}
};
struct GC {
  static void gc();
  static void register_ptr(Marked *);
  static void force_gc_all();
};

#ifdef CXBQN_MEM_shared_ptr // Use shared ptrs to manage memory

// "Owned Value"
template <typename T>
using O = std::shared_ptr<T>;

// "Weak/Unowned Value"
template <typename T> using W = std::weak_ptr<T>;

template <typename T, typename F> auto dyncast(O<F> f) {
  return std::dynamic_pointer_cast<T>(f);
}
#define CXBQN_NEW(Type, ...) make_shared<Type>(__VA_ARGS__)
#define CXBQN_SHARED_FROM_THIS() shared_from_this()

#elif CXBQN_MEM_gc // Use mark/sweep
#error "unsupported"
#elif CXBQN_MEM_leak // Leak everything

template <typename T>
using O = T *;
template <typename T> using W = T *;
template <typename T, typename F> auto dyncast(O<F> f) {
  return dynamic_cast<T *>(f);
}
#define CXBQN_NEW(Type, ...) new Type(__VA_ARGS__)
#define CXBQN_SHARED_FROM_THIS() this

#else
#error "unsupported"
#endif

using std::dynamic_pointer_cast;
using std::make_shared;
using std::experimental::make_observer;
using std::shared_ptr;
using std::experimental::observer_ptr;
using std::static_pointer_cast;
using std::weak_ptr;

} // namespace cxbqn::types
