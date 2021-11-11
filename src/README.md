## `cxbqn/src`

#### bi.cpp

The functions return a pointer to a builtin `Value` that doesn't need to be
deallocated. For example, when we need to pass a `Nothing` to something that
expects a `Value*`, we don't want to allocate a new `Nothing` every time so we
just return a pointer to a statically alloctated `Nothing` by calling
`bi_Nothing()`;

#### intructions.cpp

In `vm.hpp`, there are declarations of all the opcodes used in the BQN VM.
This source implements them.

#### types.cpp

`types.hpp` declares structures to be used throughout BQN, mostly inheriting
from the `Value` type.
[See this link for the type heirarchy.](https://gist.github.com/dzaima/e7b24e10cf6ac33f62bf8cfd80758d4b)

#### vm_macros.hpp

`vm.cpp` uses many macros to print debugging and profiling information about the
VM. We want these conditionally enabled, so debugging information is only
printed when that CMake option is enabled.

#### op.cpp

Implements operations for the opcodes used by the BQN VM. At time of writing,
this is only `u8 bc_len(u8 op)`.

#### vm.cpp

The core of the BQN VM. This loops over compiler outputs and executes opcodes,
maintaining the VM stack and managing most of the memory allocated by the VM.
