# CXBQN

VM for [BQN](https://mlochbaum.github.io/BQN/).

See [CONTRIBUTING.md](./CONTRIBUTING.md) for information on contributing.

## Building

Requires a compiler capable of C++20. GCC 9.3.1 is the oldest compiler I have tested it with.

```console
mkdir build
cd build
cmake ..
make -j12
./BQN -v
CXBQN 0.7.0
compiled on Nov 24 2021
```

## Using

```
$ ./BQN -h
CXBQN 0.7.0
compiled on Nov 24 2021
usage: BQN [options] [arguments]
	-e <string>: execute BQN expression
	-p <string>: execute BQN expression, pretty print the result
	-f <file>: execute <file>
	-r: start repl (WIP)
	-h, --help: print this message
	-v, --version: show full version information
	-x: show compilation unit before executing

$ ./BQN -e '•Show 5+5'
10

$ ./BQN -r
   foo←5
5
```

The REPL also has Readline support if you enable that option at configure time.
When you run cmake, pass the argument `-DCXBQN_READLINE=ON` like so:
```console
mkdir build && cd build
cmake .. -DCXBQN_READLINE=ON
```

If you have a readline library and development headers installed, this will use
them and provide a much nicer REPL environment with variable name completion
like so:

```
$ ./BQN -r
   foo←5
5
   foobar←10
10
   # Tab once for attempted completion
   fo<TAB>
   foo

   # Tab twice for all options if there is no single completion available
   foo<TAB><TAB>
foo     foobar
   foo
```

## Feature Support

| Spec Item          | Compliance      | Notes                                                                                                                                        |
|--------------------|-----------------|----------------------------------------------------------------------------------------------------------------------------------------------|
| Bytecode           | Full            |                                                                                                                                              |
| Runtime            | BQN-native only | Plan to replace elements of r0 then r1 with native functions                                                                                 |
| System Functions   | Partial         | See `•listsys` for the supported system values. Good candidate for first contribution.                                                       |
| Namespaces         | Partial         | Using fields of a namespace and destructuring without aliasing work, however mutable namespace fields are not supported.                     |

## Nonstandard Extensions

[See the WIP design document for parallel execution here](./doc/GPU.md).

|      Extension     | Completion |                                                                     Notes                                                                    |
|:------------------:|:----------:|:--------------------------------------------------------------------------------------------------------------------------------------------:|
| GPU Execution      | None       | Plan to add support for primitive operations on data values (chars, numbers, strings, and arrays of any of these) on GPUs in the near future |
| Threaded Execution | None       | Same plan as above. Needs more discussion                                                                                                    |
| Libraries and Packaging | None       | There has been much discussion on this topic in the Matrix server, but little consensus has been reached. The first library-related feature CXBQN will support will likely look like `strings←•Import "←strings.bqn"` where `strings.bqn` is the strings library from Marshall's [bqn-libs repository](https://github.com/mlochbaum/bqn-libs). This will likely become a *standard library* of sorts, once consensus is reached. The first character of the string argument passed to `•Import` will have some special value indicating that the BQN VM ought to look in some special location (eg all directories in the environment variable `$BQNPATH`) or perform some operation. |
