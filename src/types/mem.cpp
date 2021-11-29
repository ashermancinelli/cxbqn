#include <cxbqn/mem.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

static std::vector<Marked *> allocations;

void GC::register_ptr(Marked * mem) {
  allocations.push_back(mem);
}

void GC::gc() {
  // Do nothing for now... have to figure out what is classified as a root
  // object before we can mark/sweep.
}

void GC::force_gc_all() {
  for (auto *e : allocations)
    if (nullptr != e)
      delete e;
}

}
