# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.9.0] 12-22-2021

* Add the cxbqn-config utility and install all targets
* Update documentation
* Add FFI as `•_FFI_`

## [0.8.2] 12-21-2021

* Add swath of CUDA functions under `•_CUDAFor`

## [0.8.1] 11-29-2021

* Use observer ptrs for most pointers, leak just like CBQN. Huge perf boost.

## [0.8.0] 11-28-2021

* Add memory mangement policies

## [0.7.0] 11-24-2021

* Significant improvements to the driver
* Working repl
* Readline support for the repl
* made public!

## [0.6.0] 11-19-2021

* Significant improvements to the driver
* Significant performance improvements

## [0.5.0] 11-18-2021

* Significant improvements to the driver
* support for gcc 9

## [0.4.1] 11-18-2021

* Formatter working
* Compiler compiling string
* Passing under, undo, and identity tests

## [0.4.0] 11-18-2021

* Pretty backtraces
* passing l1, 2, 3, 4, 5, 6 prim tests
* building compiler
* added support for source locations

## [0.3.2] 11-14-2021

* Passing l0 prim tests, still failing a few later prim tests.

## [0.3.0] 11-9-2021

* Fixed significant memory management issues. Now fit runtime in 2-4mib of ram.

## [0.2.0] 11-11-2021

* passing all simple and primitive tests
* successfully loading runtime
* added some memory management
    * memory still going wild when loading the compiler

## [0.1.0] 11-4-2021

* VM passing 100% of bytecode tests as described in `BQN/test/cases/bytecode.bqn`
* VM passing many simple and primitive tests.

## [0.0.2] 10-24-2021

* `Type` primitive
* infrastructure for dynamically generating bytecode tests from upstream BQN repo

## [0.0.1] 10-22-2021

* Initial repo. Referring to [ebqn-rs](https://github.com/cannadayr/ebqn-rs/blob/master/crs.bqn) for structures and [the old bqn javascript runtime](https://github.com/mlochbaum/BQN/blob/f74d9223ef880f2914030c2375f680dcc7e8c92b/bqn.js#L23) to get started.
* Formatting targets
* README, LICENSE, CHANGELOG
