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
#include <spdlog/fmt/bundled/ostream.h>
#include <spdlog/fmt/ostr.h>
#include <tuple>
#include <type_traits>
#include <utf8.h>
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
  t_Deferred,

  // Because •Type of an array is 0, checking for bits to test for an array
  // is not effective.
  t_RefArray,

  // If a type does not override Value::t_ for some reason, this will be its
  // type
  t_Opaque,
  t_BlockInst,

  // The value of 𝕨 in monadic calls
  t_Nothing,

  // Builtin host-side functions for bootstrapping the runtime
  t_Primitive,

  // Some operations can only take certain combinations of data values, eg +.
  t_DataValue,
  t_String,
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

// "Owned Value"
template <typename T> using O = std::shared_ptr<T>;

// "Weak/Unowned Value"
template <typename T> using W = std::weak_ptr<T>;

struct Scope;
struct Block;

struct Value {

  // When blocks are not immediate, we sometimes need to cache arguments to be
  // referred to later. For example, a modifier block may need to refer both to
  // the modifier arguments (𝕣𝕗𝕘) as well as the function arguments (𝕤𝕩𝕨). In
  // this case, when the modifier is defined, 𝕣 𝕗 and 𝕘 are stored in
  // deferred_args so they can be copied into the scope when the function
  // arguments are present.
  std::vector<O<Value>> deferred_args;
  Value() : deferred_args(6, nullptr) {}

  virtual ~Value() {}

  // A type must be able to tell you it's •Type. We also use this over trying to
  // dynamic cast to a bunch of different types since the object creation
  // required to attempt a dynamic cast can be very costly. Calling t() before a
  // dyn cast lets us know for sure that the dyn cast will succeed.
  virtual TypeType t() const { return TypeType{annot(t_Opaque)}; }

  // If a value type does not define it's own call, we probably just push it
  // back on the stack.
  virtual O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) {
    return std::shared_ptr<Value>(this);
  };

  virtual std::ostream &repr(std::ostream &os) const { return os << "V"; }
};

struct Nothing : public Value {
  TypeType t() const override { return TypeType{annot(t_Nothing)}; }
  std::ostream &repr(std::ostream &os) const override { return os << "·"; }
};
O<Value> bi_Nothing();

struct Number : public Value {
  f64 v;
  Number(f64 v) : v{v} {}
  TypeType t() const override {
    return TypeType{t_Number | annot(t_DataValue)};
  }
  std::ostream &repr(std::ostream &os) const override {
    return (v == std::numeric_limits<f64>::infinity()
                ? os << "∞"
                : v == -std::numeric_limits<f64>::infinity() ? os << "¯∞"
                                                             : os << v);
  }
};

struct Character : public Number {
  Character(c32 c) : Number{static_cast<f64>(c)} {}
  TypeType t() const override {
    return TypeType{t_Character | annot(t_DataValue)};
  }
  inline c32 c() const { return static_cast<c32>(v); }
  std::ostream &repr(std::ostream &os) const override {
    return os << "ch=" << v;
    if (c() == '\0') {
      return os << "'@'";
    }
    std::string s;
    utf8::append(c(), s);
    fmt::print(os, "'{}'", s);
    return os;
  }
};

struct Array : public Value {
  std::vector<O<Value>> values;
  std::vector<uz> shape;
  Array(const uz N, std::deque<O<Value>> &stk);
  Array(std::vector<O<Value>> vs) : values{vs}, shape{vs.size()} {}
  inline const uz N() const {
    const auto N = values.size();
#ifdef CXBQN_DEEPCHECKS
    if (N !=
        std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<uz>()))
      throw std::runtime_error("cxbqn internal:shape does not match values");
#endif
    return N;
  }
  Array(uz N) {
    shape.push_back(N);
    values.resize(N);
  }
  Array(const std::u32string &s) {
    shape.push_back(s.size());
    values.reserve(s.size());
    for (const auto &c : s)
      values.push_back(O<Value>(new Character(c)));
    extra_annot |= annot(t_String);
  }
  Array() {}
  ~Array() {}
  TypeType extra_annot{0};
  TypeType t() const override { return TypeType{t_Array} | extra_annot; }
  std::ostream &repr(std::ostream &os) const override;
};

struct Reference : public Value {
  uz depth;
  uz position_in_parent;
  Reference(uz d, uz p) : depth{d}, position_in_parent{p} {}
  TypeType t() const override { return TypeType{annot(t_Reference)}; }
  std::ostream &repr(std::ostream &os) const override {
    return os << "(d=" << depth << ",p=" << position_in_parent << ")";
  }
};

struct RefArray : public Array {
  RefArray(const ByteCode::value_type N, std::deque<O<Value>> &stk)
      : Array(N, stk) {}
  Reference *getref(uz idx);
  TypeType t() const override {
    return TypeType{t_Array | annot(t_Reference) | annot(t_RefArray)};
  }
  std::ostream &repr(std::ostream &os) const override;
};

struct Function : public Value {
  TypeType t() const override { return TypeType{t_Function}; }
  std::ostream &repr(std::ostream &os) const override { return os << "F"; }
};

struct BlockInst : public Function {
  Scope *scp;
  uz blk_idx;

  // Is the block at index blk_idx immediate?
  bool imm() const;

  TypeType t() const override { return TypeType{annot(t_BlockInst)}; }
  BlockInst(Scope *scp, uz blk_idx) : scp{scp}, blk_idx{blk_idx} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "Block{i=" << blk_idx << "}";
  }
};

struct Fork : public Function {
  O<Value> f, g, h;
  Fork(O<Value> f, O<Value> g, O<Value> h) : f{f}, g{g}, h{h} {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Atop : public Function {
  O<Value> g, f;
  Atop(O<Value> f, O<Value> g) : f{f}, g{g} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Md1 : public Function {
  TypeType t() const override { return TypeType{t_Md1}; }
};

struct UserMd1 : public Md1 {
  TypeType t() const override { return TypeType{t_Md1 | annot(t_UserDefined)}; }
  Scope *sc;
  Block *bl;
};

struct Md2 : public Function {
  TypeType t() const override { return TypeType{t_Md2}; }
};

struct UserMd2 : public Md2 {
  TypeType t() const override { return TypeType{t_Md2 | annot(t_UserDefined)}; }
  Scope *sc;
  Block *bl;
};

/*
 * When a modifier is popped off the stack and it not immediate, this type
 * is pushed back on the stack
 */
struct Md1Deferred : public Function {
  TypeType t() const override { return TypeType{t_Md1 | annot(t_Deferred)}; }
  O<Value> f, m1;
  Md1Deferred(O<Value> f, O<Value> m1) : f{f}, m1{m1} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

/*
 * Same as above, but two modifier
 */
struct Md2Deferred : public Function {
  TypeType t() const override { return TypeType{t_Md2 | annot(t_Deferred)}; }
  O<Value> f, m2, g;
  Md2Deferred(O<Value> f, O<Value> m2, O<Value> g) : f{f}, m2{m2}, g{g} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct CompilationResult {
  i32 *bc;
  O<Value> objs;
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
  std::pair<ByteCode, uz> body(u8 nargs = 0) const;

  uz max_nvars() const;

  Block(ByteCodeRef bc, BlockDef bd, std::span<Body> bods);

private:
  // modification of this should not affect constness since it doesn't affect
  // idempotency of the call, in particular `max_nvars`
  mutable std::optional<uz> cached_max_nvars;

  // Span of bytecode, so we can retrieve a subspan for a
  // monadic/dyadic/immediate invokation of the block as needed.
  ByteCode bc;

  std::vector<Body> bods;
};

struct Scope {
  Scope *parent;
  std::vector<O<Value>> vars;
  std::vector<O<Value>> consts;
  std::vector<Block> blks;
  const uz blk_idx;
  Scope(Scope *parent, std::vector<Block> blks, uz blk_idx,
        std::optional<std::vector<O<Value>>> consts = nullopt);
  O<Value> get(Reference *r);
  void set(bool should_var_be_set, Reference *r, O<Value> v);
  Scope *get_nth_parent(uz depth);
};

} // namespace types
} // namespace cxbqn
