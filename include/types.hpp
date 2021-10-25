#pragma once
#include <functional>
#include <initializer_list>
#include <numeric>
#include <scalar_types.hpp>
#include <type_traits>
#include <variant>
#include <memory>

namespace cxbqn {

// template deduction guides to make std::visit feel better
template <class... Ts> struct overload : Ts... { using Ts::operator()...; };
template <class... Ts> overload(Ts...) -> overload<Ts...>;

// for nice enum->int casting
template <typename E> constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

template <typename T> using initl = std::initializer_list<T>;

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

enum Types {
  t_Array=0,
  t_Number,
  t_Character,
  t_Function,
  t_Md1,
  t_Md2,
  t_Namespace,
  NUM_TYPES
};

struct Value {
  i32 refc;
  virtual ~Value() = default;
  virtual u8 t() const = 0;
};

// Managed Value
using MValue = std::shared_ptr<Value>;

struct Nothing : public Value {};

struct Character : public Value {
  char v;
  Character(char c) : v{c} {}
  u8 t() const override { return 2; }
};

struct Number : public Value {
  f64 v;
  Number(f64 v) : v{v} {}
  u8 t() const override { return 1; }
};

struct Array : public Value {
  std::vector<uz> shape;
  f64 *values;
  Array(initl<f64> vs);
  Array(initl<uz> szs, initl<f64> vs);
  Array();
  ~Array();
  u8 t() const override { return 0; }
};

struct Reference : public Value {
  uz dis_from_parent;
  uz position_in_parent;
};

struct Function : public Value {
  u8 t() const override { return 3; }
};

struct Builtin : public Function {
  virtual Value *operator()(Value *x) = 0;
  virtual Value *operator()(Value *w, Value *x) = 0;
};

struct UserFn : public Function {};

struct Fork : public Function {
  Value *f, *g, *h;
};

struct Atop : public Function {
  Value *g, *h;
};

struct Md1 : public Function {
  u8 t() const override { return 4; }
};

struct Scope;
struct Block;

struct UserMd1 : public Md1 {
  Scope *sc;
  Block *bl;
};

struct Md2 : public Function {
  u8 t() const override { return 5; }
};

struct UserMd2 : public Md2 {
  Scope *sc;
  Block *bl;
};

struct Md1Derived : public Function {
  Value *f, *m1;
};

struct Md2Derived : public Function {
  Value *f, *m2, *g;
};

struct Scope {
  Scope *parent;
  Value *vars[];
};

struct CompilationResult {
  i32 *bc;
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
  uz body_idx;
  Block(uz ty, uz immediate, uz idx);
  ~Block();
};

template <typename T> void is(Value *v);

} // namespace types
} // namespace cxbqn

#include "detail/types.hpp.inl"
