#pragma once
#include <cxbqn/types.hpp>
#include <cxbqn/array_types.hpp>

namespace cxbqn::types {
std::vector<O<Value>> values(O<ArrayBase> const arr);
std::string to_string(O<Value> const arr);
}
