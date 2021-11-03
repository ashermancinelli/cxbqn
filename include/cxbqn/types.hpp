#pragma once
#include <bitset>
#include <cxbqn/scalar_types.hpp>
#include <deque>
#include <functional>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <optional>
#include <span>
#include <spdlog/fmt/ostr.h>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

namespace cxbqn {

using std::nullopt;

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

// The value of •Type for a given value is `myval.t_&7` as the builtin type
// is stored in the first three bits of the type field.
enum Types {
  t_Array = 0,
  t_Number,
  t_Character,
  t_Function,
  t_Md1,
  t_Md2,
  t_Namespace,
};

// The bit represeting (1 << t_Annotation) in the type of a value represents
// the value of a given type annotation.
//
// Eg an array reference would have `0b000 | (1<<t_Reference)` since 0b000 is
// type value 0 as prescribed in the spec, and 1<<t_Reference indicates the
// reference annotation.
enum TypeAnnotations {
  // After the namespace type, all other "types" are used internally only.
  // The first 3 bits of the type of a value represent the return of •Type on
  // that value, and the rest are internal annotations that may be associated
  // with a type, eg an array reference will have type t_Array|t_Reference
  t_Reference = 3,
  t_UserDefined,
  t_Derived,

  // Because •Type of an array is 0, checking for bits to test for an array
  // is not effective.
  t_RefArray,

  // If a type does not override Value::t_ for some reason, this will be its
  // type
  t_Opaque,
  t_BlockInst,

  // The value of 𝕨 in monadic calls
  t_Nothing,
};

static constexpr u32 annot(TypeAnnotations ta) { return 1 << ta; }

// The type used to represent the •Type of a value along with some internal
// type annotations, eg references and uniform arrays.
//
// Size is 32 even though we will likely never have this many internal type
// annotations, but the smallest number we can turn a bitset into is a ulong,
// so we might as well have access to that much data.
using TypeType = std::bitset<32>;

using ByteCode = std::vector<i32>;
using ByteCodeRef = std::span<i32>;

struct Scope;
struct Block;

struct Value {

  // When blocks are not immediate, we sometimes need to cache arguments to be
  // referred to later. For example, a modifier block may need to refer both to
  // the modifier arguments (𝕣𝕗𝕘) as well as the function arguments (𝕤𝕩𝕨). In
  // this case, when the modifier is defined, 𝕣 𝕗 and 𝕘 are stored in
  // deferred_args so they can be copied into the scope when the function
  // arguments are present.
  std::vector<Value *> deferred_args;
  Value() : deferred_args(6, nullptr) {}

  virtual ~Value() {}

  // A type must be able to tell you it's •Type. We also use this over trying to
  // dynamic cast to a bunch of different types since the object creation
  // required to attempt a dynamic cast can be very costly. Calling t() before a
  // dyn cast lets us know for sure that the dyn cast will succeed.
  virtual TypeType t() const { return TypeType{annot(t_Opaque)}; }

  // If a value type does not define it's own call, we probably just push it
  // back on the stack.
  virtual Value *call(u8 nargs = 0, initl<Value *> args = {}) { return this; };

  virtual std::ostream &repr(std::ostream &os) const { return os << "V"; }
};

struct Nothing : public Value {
  TypeType t() const override { return TypeType{annot(t_Nothing)}; }
};

// Managed Value
// Currently unused, but might be used for managing memory later on. The stack
// and scope will likely own their values, while all other values can just hold
// a weak reference since they share a common ancestor (the root scope).
using OwnedV = std::shared_ptr<Value>;
using WeakV = std::weak_ptr<Value>;

struct Character : public Value {
  char v;
  Character(char c) : v{c} {}
  virtual TypeType t() const { return TypeType{t_Character}; }
  std::ostream &repr(std::ostream &os) const override {
    return os << v;
  }
};

struct Number : public Value {
  f64 v;
  Number(f64 v) : v{v} {}
  virtual TypeType t() const { return TypeType{t_Number}; }
  std::ostream &repr(std::ostream &os) const override {
    return os << v;
  }
};

struct Array : public Value {
  const uz N;
  std::vector<Value *> values;
  Array(const ByteCode::value_type N, std::deque<Value *> &stk);
  Array(uz N) : N{N} {}
  ~Array() {}
  virtual TypeType t() const { return TypeType{t_Array}; }
  std::ostream &repr(std::ostream &os) const override;
};

struct Reference : public Value {
  uz depth;
  uz position_in_parent;
  Reference(uz d, uz p) : depth{d}, position_in_parent{p} {}
  virtual TypeType t() const { return TypeType{annot(t_Reference)}; }
  std::ostream &repr(std::ostream &os) const override {
    return os << "(d=" << depth << ",p=" << position_in_parent << ")";
  }
};

struct RefArray : public Array {
  RefArray(const ByteCode::value_type N, std::deque<Value *> &stk)
      : Array(N, stk) {}
  Reference *getref(uz idx);
  virtual TypeType t() const {
    return TypeType{t_Array | annot(t_Reference) | annot(t_RefArray)};
  }
  std::ostream &repr(std::ostream &os) const override;
};

struct Function : public Value {
  virtual TypeType t() const { return TypeType{t_Function}; }
  std::ostream &repr(std::ostream &os) const override { return os << "F"; }
};

struct Builtin : public Function {
  virtual Value *operator()(Value *x) = 0;
  virtual Value *operator()(Value *w, Value *x) = 0;
};

struct BlockInst : public Function {
  Scope *scp;
  uz blk_idx;

  // Is the block at index blk_idx immediate?
  bool imm() const;

  virtual TypeType t() const { return TypeType{annot(t_BlockInst)}; }
  BlockInst(Scope *scp, uz blk_idx) : scp{scp}, blk_idx{blk_idx} {}
  Value *call(u8 nargs = 0, initl<Value *> args = {}) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "Block{i=" << blk_idx << "}";
  }
};

struct Fork : public Function {
  Value *f, *g, *h;
  Fork(Value*f, Value*g, Value*h) : f{f}, g{g}, h{h} {}
  Value *call(u8 nargs = 0, initl<Value *> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Atop : public Function {
  Value *g, *f;
  Atop(Value* f, Value* g) : f{f}, g{g} {}
  Value *call(u8 nargs = 0, initl<Value *> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Md1 : public Function {
  virtual TypeType t() const { return TypeType{t_Md1}; }
};

struct UserMd1 : public Md1 {
  virtual TypeType t() const { return TypeType{t_Md1 | annot(t_UserDefined)}; }
  Scope *sc;
  Block *bl;
};

struct Md2 : public Function {
  virtual TypeType t() const { return TypeType{t_Md2}; }
};

struct UserMd2 : public Md2 {
  virtual TypeType t() const { return TypeType{t_Md2 | annot(t_UserDefined)}; }
  Scope *sc;
  Block *bl;
};

struct Md1Derived : public Function {
  virtual TypeType t() const { return TypeType{t_Md1 | annot(t_Derived)}; }
  Value *f, *m1;
};

struct Md2Derived : public Function {
  virtual TypeType t() const { return TypeType{t_Md2 | annot(t_Derived)}; }
  Value *f, *m2, *g;
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
 * \brief Blocks as they are passed from compiled output are seperate from the
 * bodies. This structure represents only the block information as passed in.
 * This type is then used to construct the true `Block` structure, which is more
 * useful at runtime.
 */
struct BlockDef {
  BlockType type;
  bool immediate;
  CompilationResult *comp;

  // FIXME: body_idx and mon/dya indices should really be a variant

  // "ambivalent index", which is used in immediate blocks
  uz body_idx;

  // list of bodies to try executing in sequence for monadic and dyadic calls
  std::vector<uz> mon_body_idxs;
  std::vector<uz> dya_body_idxs;

  BlockDef(uz ty, uz immediate, uz idx);
  BlockDef(uz ty, uz immediate, std::vector<std::vector<uz>> indices);
  ~BlockDef();
};

struct Block {
  const BlockDef def;

  // Gives the bytecode and number of variables for a given call
  std::pair<ByteCodeRef, uz> body(u8 nargs = 0) const;

  uz max_nvars() const;

  Block(ByteCodeRef bc, BlockDef bd, std::span<Body> bods);

private:
  // modification of this should not affect constness since it doesn't affect
  // idempotency of the call, in particular `max_nvars`
  mutable std::optional<uz> cached_max_nvars;

  // Span of bytecode, so we can retrieve a subspan for a
  // monadic/dyadic/immediate invokation of the block as needed.
  ByteCodeRef bc;

  std::span<Body> bods;
};

struct Scope {
  Scope *parent;
  std::vector<Value *> vars;
  std::span<Value *> consts;
  std::span<Block> blks;
  const uz blk_idx;
  Scope(Scope *parent, std::span<Block> blks, uz blk_idx,
        std::optional<std::span<Value *>> consts = nullopt);
  Value *get(Reference *r);
  void set(bool should_var_be_set, Reference *r, Value *v);
  Scope *get_nth_parent(uz depth);
};

template <typename T> void is(Value *v);

} // namespace types
} // namespace cxbqn

#include "detail/types.hpp.inl"
