# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
