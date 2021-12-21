#include "sys_helper.hpp"
#include <dlfcn.h>

namespace cxbqn::sys {

O<Value> FFI::call(u8 nargs, Args& args) {
  CXBQN_DEBUG("•FFI: nargs={},args={}", nargs, args);
  fmt::print("here\n");

  auto libname = dyncast<Array>(args[4])->to_string();
  auto funcname = dyncast<Array>(args[5])->to_string();

  auto* handle = dlopen(libname.c_str(), RTLD_LAZY);
  if (!handle) {
    std::cout << "CXBQN internal ffi error: " << dlerror() << "\n";
    return CXBQN_NEW(Number, 1);
  }

  dlerror(); // clear errors

  // Without type punning:
  // f64 (*userfn)(u8, Value**)
  f64 (*userfn)(u8, void*);

  // Yes, this looks awful, but it's what's recomended by `man 3 dlopen` so it's
  // what I'll use
  *(void**)(&userfn) = dlsym(handle, funcname.c_str());
  if (!userfn) {
    std::cout << "CXBQN internal ffi error: " << dlerror() << "\n";
    return CXBQN_NEW(Number, 1);
  }

  auto** userargs = new Value*[args.size()];
  std::copy(args.begin(), args.end(), userargs);
  auto ret = (*userfn)(nargs, userargs);
  delete[] userargs;
  dlclose(handle);

  return CXBQN_NEW(Number, ret);
}

}
