## Foreign Function Interface
_since 0.9.0_

The system function `"libmylib.so" •_FFI_ "userfunc"` takes two strings as the path to the shared library and the name of the function you would like to extract, and returns a function that will call the function from the shared library.
This is a very thin wrapper around `dlopen`.
See [`man 3 dlopen`](https://man7.org/linux/man-pages/man3/dlopen.3.html) for more documentation.

Example user function:

```cpp
$ echo '
#include <cstdint>
#include <cstddef>
#include <iostream>
extern "C" double userfn(uint8_t nargs, void* args) {
  std::cout << "Calling into CXBQN from FFI!\n";
  return 0.0;
}
' >> userfn.cpp
$ mkdir build && cd build && cmake .. -DCXBQN_FFI=ON && make -j 12
$ g++ -fPIC -c -o userfn.o userfn.cpp
$ g++ -o userfn.so userfn.o
$ ./BQN -e '"tmp.so" •_FFI_ "userfn" @'
Calling into CXBQN from FFI!
```

***This FFI API will certainly change. Do not consider this stable. This functionality is just for playing around with the possibilities, not for any production use.***
