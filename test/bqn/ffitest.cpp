#include <cstdint>
#include <cstddef>
#include <iostream>
extern "C" double userfn(uint8_t nargs, void* args) {
  std::cout << "Calling into CXBQN from FFI!\n";
  return 0.0;
}
