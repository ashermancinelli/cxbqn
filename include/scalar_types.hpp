#pragma once

namespace cxbqn {

using u8 = uint8_t;
using u64 = uint64_t;
using uz = std::size_t;

static_assert("Only 64b systems" && sizeof(double)==8);
using f64 = double;

}
