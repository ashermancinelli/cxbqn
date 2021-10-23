#pragma once
#include <numeric>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <variant>
#include <scalar_types.hpp>

namespace cxbqn {

// template deduction guides to make std::visit feel better
template <class... Ts> struct overload : Ts... { using Ts::operator()...; };
template <class... Ts> overload(Ts...) -> overload<Ts...>;

// for nice enum->int casting
template <typename E> constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

template<typename T> using initl = std::initializer_list<T>;

namespace types {

/**
 *
 * Type heirarchy:
 * https://gist.github.com/dzaima/e7b24e10cf6ac33f62bf8cfd80758d4b
 *
 * Example output of cjs.bqn:
 *
 * \code{.sh}
 * $ BQN ./ext/bqn/src/cjs.bqn '5+5'
 * [[0,1,0,0,0,1,17,7],[runtime[0],5],[[0,1,0]],[[0,0]]]
 * \endcode
 *
 * bytecode sequence = [0,1,0,0,0,1,17,7]
 * constants = [runtime[0],5]
 * blocks = [[0,1,0]]
 * bodies = [[0,0]]
 *
 */

struct Value {
  i32 refc;
};

struct Nothing : Value {};

struct Character {
  char v;
};

// Using cbqn's enum
enum class NumType {
  bit = 0,
  i8 = 1,
  i16 = 2,
  i32 = 3,
  f64 = 4,
};

struct Number : Value {
  NumType t;
  union {
    i8 _i8;
    i16 _i16;
    i32 _i32;
    f64 _f64;
  } v;
};

template <typename T> struct Array : Value {
  std::vector<uz> shape;
  T *values;
  Array(std::initializer_list<T> vs);
  Array(std::initializer_list<uz> szs, std::initializer_list<T> vs);
  Array();
  ~Array();
};

struct Reference : Value {
  uz dis_from_parent;
  uz position_in_parent;
};

struct Function : Value {};

struct UserFn : Function{};

struct Fork : Function {
  Value *f, *g, *h;
};

struct Atop : Function {
  Value *g, *h;
};

struct Md1 : Function {};

struct Scope;
struct Block;

struct UserMd1 : Md1 {
  Scope *sc;
  Block *bl;
};

struct Md2 : Function {};

struct UserMd2 : Md2 {
  Scope *sc;
  Block *bl;
};

struct Md1Derived : Function {
  Value *f, *m1;
};

struct Md2Derived : Function {
  Value *f, *m2, *g;
};

struct Scope {
  Scope *parent;
  Value *vars[];
};

struct CompilationResult {
  uz *bc;
  Value *objs;
};

enum class BlockType {
  func = 0,
  md1 = 1,
  md2 = 2,
};

struct Body {
  uz bc_offset;
  uz var_count;
};

/**
 * Block without multiple bodies
 */
struct Block {
  BlockType type;
  bool immediate;
  CompilationResult *comp;
  uz bc_offset;
  uz var_count;
};

} // namespace types
} // namespace cxbqn

#include "types.hpp.inl"
