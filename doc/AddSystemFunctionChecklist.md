## Adding a System Function

This checklist enumerates the steps needed to add a system function to CXBQN.

1. Add the declaration to `include/cxbqn/sys.hpp`
1. Add the name of the system function to the vector of strings in `src/sys/sys_function_resolver.cpp`
1. Check for the name of the system function and append to the system function table in `src/sys/sys_function_resolver.cpp` if found
1. Add a test
