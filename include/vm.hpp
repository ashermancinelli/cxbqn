#pragma once
#include <vector>
#include <cstdint>
#include <optional>
#include <memory>

#include <value_types.hpp>

namespace cxbqn::vm {

struct Env {
};

using Bytecode = std::vector<std::size_t>;
using Objects = std::vector<std::optional<Value>>;

struct Sections {

};

struct Code {
  Bytecode bc;
  
};

int vm(Env &e, Code& code, std::size_t &prog_counter, std::vector<int>& stack);
int run(Bytecode &bytecode, Objects &objects, Sections &sections);

}
