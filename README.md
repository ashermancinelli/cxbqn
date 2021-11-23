## cxbqn

VM for [BQN](https://mlochbaum.github.io/BQN/).

## Building

Requires a compiler capable of C++20. GCC 9.3.1 is the oldest compiler I have tested it with.

```console
mkdir build
cd build
cmake ..
mkae -j12
./BQN -e '5+5'
```
