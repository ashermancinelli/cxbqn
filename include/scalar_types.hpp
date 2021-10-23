#pragma once

namespace cxbqn {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using uz = std::size_t;

static_assert("Only 64b systems" && sizeof(double) == 8);
using f64 = double;
using f32 = float;

} // namespace cxbqn
