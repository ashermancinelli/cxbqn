# CXBQN

VM for [BQN](https://mlochbaum.github.io/BQN/).

## Building

Requires a compiler capable of C++20. GCC 9.3.1 is the oldest compiler I have tested it with.

```console
mkdir build
cd build
cmake ..
make -j12
./BQN -e '5+5'
```

## Feature Support

| Spec Item          | Compliance      | Notes                                                                                                                                        |
|--------------------|-----------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| Bytecode           | Full            |                                                                                                                                              |
| Runtime            | BQN-native only | Plan to replace elements of r0 then r1 with native functions                                                                                 |
| System Functions   | Partial         | See `•listsys` for the supported system values. Good candidate for first contribution.                                                       |
| Namespaces         | Partial         | Using fields of a namespace and destructuring without aliasing work, however mutable namespace fields are not supported.                     |

## Nonstandard Extensions

| Extension          | Completion      | Notes                                                                                                                                        |
|--------------------|-----------------|----------------------------------------------------------------------------------------------------------------------------------------------|

| GPU Execution      | None            | Plan to add support for primitive operations on data values (chars, numbers, strings, and arrays of any of these) on GPUs in the near future |
| Threaded Execution | None            | Same plan as above. Needs more discussion                                                                                                    |
