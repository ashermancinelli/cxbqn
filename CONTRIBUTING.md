## Contributing

Most low-hanging fruit in CXBQN involves system functions (such as `•FChars`)
that have not been implemented yet.
To add a system value, see `include/cxbqn/sys.hpp`, particularly towards the
bottom.
Here I have many system functions already declared, and defined in `src/sys/`.
If the system function requires a value from the runtime environment (such as
the runtime itself, or the compiled BQN formatter), simply take that item as a
constructor and pass the field when constructing the system function in
`src/sys/sys_function_resolver.cpp`.

The system function `•Exit` is a great example of a simple system function.
The constructor takes no arguments, so it uses a macro in
`include/cxbqn/sys.hpp`, but it's declaration is as simple as:

```cpp
// see include/cxbqn/sys.hpp
struct Exit : public Function {                                                   
  std::ostream &repr(std::ostream &os) const override {                      
    return os << "•Exit";                                                
  }                                                                          
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;     
};                                                                           
```

and the definition is extremely simple as well:
```cpp
// see src/sys/exit.cpp
O<Value> Exit::call(u8 nargs, std::vector<O<Value>> args) {
  auto n = dynamic_pointer_cast<Number>(args[1])->v;
  std::exit(n);
}
```

To find a system function to write, see the
[specification for system values](https://mlochbaum.github.io/BQN/spec/system.html)
and find one not already in `include/cxbqn/sys.hpp`.
Feel free to email me at ashermancinelli@gmail.com with questions, or better yet,
[join the Matrix server](https://mlochbaum.github.io/BQN/community/forums.html).

I would also love help implementing a garbage collector, however this will be
far more involved.
