#pragma once
#include <bitset>
#include <cxbqn/mem.hpp>
#include <cxbqn/scalar_types.hpp>
#include <functional>
#include <initializer_list>
#include <map>
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
  t_Alias,

  // Typed arrays have annotations indicating the type
  t_TypedArray,
  t_I64Array,
  t_F64Array,
  t_UZArray,
  t_C32Array,

  // For NOTM. Indicates assigning to this reference should do nothing
  t_NullReference,
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
using ByteCodeRef = std::span<const i32>;

struct Scope;
struct Block;
struct Array;
struct Value;

using Args = std::array<O<Value>, 6>;

struct Value : public std::enable_shared_from_this<Value>, public Marked {

  Value() { GC::register_ptr(this); }

  virtual ~Value() {}

  // First we have to determine what ought to be a "root" value before GC'ing
  // is actually helpful. Until then, this will proabably be empty.
  virtual void mark() {}

  // A type must be able to tell you it's •Type. We also use this over trying to
  // dynamic cast to a bunch of different types since the object creation
  // required to attempt a dynamic cast can be very costly. Calling t() before a
  // dyn cast lets us know for sure that the dyn cast will succeed.
  virtual TypeType t() const { return TypeType{annot(t_Opaque)}; }

  // If a value type does not define it's own call, we probably just push it
  // back on the stack.
  virtual O<Value> call(u8 nargs, Args &args) {
    return CXBQN_SHARED_FROM_THIS();
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
  virtual TypeType t() const override {
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
  virtual TypeType t() const override {
    return TypeType{t_Character | annot(t_DataValue)};
  }
  inline c32 c() const { return static_cast<c32>(v); }
  std::ostream &repr(std::ostream &os) const override {
    return os << "ch=" << v;
    // if (c() == '\0') {
    //   return os << "'@'";
    // }
    // std::string s="";
    // utf8::append(c(), std::back_inserter(s));
    // fmt::print(os, "'{}'", s);
    // return os;
  }
};

// For when we could be working with either a typed array or a heterogeneous
// array
struct ArrayBase : public Value {
  ArrayBase(std::vector<uz> sh) : shape{sh} {}
  ArrayBase() {}
  std::vector<uz> shape;
  virtual O<Value> get(uz i) const = 0;
  virtual uz N() const = 0;
  virtual O<ArrayBase> copy() const = 0;
};

struct Array : public ArrayBase {
  std::vector<O<Value>> values;
  Array(const uz N, std::vector<O<Value>> &stk);
  Array(std::vector<O<Value>> vs) : values{vs} { shape.push_back(vs.size()); }
  Array(std::vector<O<Value>> vs, std::vector<uz> shape)
      : values{vs}, ArrayBase(shape) {}
  uz N() const override;
  Array(uz N) {
    shape.push_back(N);
    values.resize(N);
  }
  Array(const std::string &s);
  Array(const std::u32string &s);

  // For typed arrays, the BQN value will have to be constructed on the fly.
  O<Value> get(uz i) const override { return values[i]; }

  // For typed arrays, we want to create a copy of ourselves
  O<ArrayBase> copy() const override { return CXBQN_NEW(Array, values, shape); }

  Array() {}
  ~Array() {}
  TypeType extra_annot{0};
  TypeType t() const override { return TypeType{t_Array} | extra_annot; }
  std::ostream &repr(std::ostream &os) const override;
};

struct Reference : public Value {
  uz depth;
  uz position_in_parent;
  std::optional<std::string> tag = nullopt;
  Reference(uz d, uz p) : depth{d}, position_in_parent{p} {}
  TypeType extra_annot;
  TypeType t() const override {
    return TypeType{annot(t_Reference)} | extra_annot;
  }
  std::ostream &repr(std::ostream &os) const override {
    return os << "(d=" << depth << ",p=" << position_in_parent << ")";
  }
};

struct RefArray : public Array {
  RefArray(const ByteCode::value_type N, std::vector<O<Value>> &stk)
      : Array(N, stk) {}
  O<Reference> getref(uz idx);
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
  observer_ptr<Scope> scp;
  uz blk_idx;

  u32 type;
  TypeType t() const override { return TypeType{type | annot(t_BlockInst)}; }

  bool imm() const;

  BlockInst(observer_ptr<Scope> scp, uz blk_idx);

  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override {
    return os << "Block{i=" << blk_idx << "}";
  }
};

struct Fork : public Function {
  O<Value> f, g, h;
  Fork(O<Value> f, O<Value> g, O<Value> h) : f{f}, g{g}, h{h} {}
  TypeType t() const override { return TypeType{t_Function}; }
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Atop : public Function {
  O<Value> g, f;
  Atop(O<Value> f, O<Value> g) : f{f}, g{g} {}
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override;
};

/*
 * When a modifier is popped off the stack and it not immediate, this type
 * is pushed back on the stack
 */
struct Md1Deferred : public Function {
  TypeType t() const override {
    return TypeType{t_Function | annot(t_Deferred)};
  }
  O<Value> f, m1;
  Md1Deferred(O<Value> f, O<Value> m1) : f{f}, m1{m1} {}
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Md1 : public Function {
  TypeType t() const override { return TypeType{t_Md1}; }
};

/*
 * Same as above, but two modifier
 */
struct Md2Deferred : public Function {
  TypeType t() const override {
    return TypeType{t_Function | annot(t_Deferred)};
  }
  O<Value> f, m2, g;
  Md2Deferred(O<Value> f, O<Value> m2, O<Value> g) : f{f}, m2{m2}, g{g} {}
  O<Value> call(u8 nargs, Args &args) override;
  std::ostream &repr(std::ostream &os) const override;
};

struct Md2 : public Function {
  TypeType t() const override { return TypeType{t_Md2}; }
};

struct Namespace : public Value {
  observer_ptr<Scope> _scp;
  Namespace(observer_ptr<Scope> scp) : _scp{scp} {}
  Namespace() : _scp{nullptr} {}
  virtual O<Value> get(const std::string &n);
  virtual O<Value> get(uz i);
  virtual O<Value> set(bool should_be_set, const std::string &n, O<Value> v);
  virtual O<Value> set(bool should_be_set, uz n, O<Value> v);
  TypeType t() const override {
    return TypeType{t_Namespace | annot(t_UserDefined)};
  }
  std::ostream &repr(std::ostream &os) const override;
};

struct BuiltinNamespace : public Namespace {
  virtual O<Value> get(const std::string &n) = 0;
  TypeType t() const override { return TypeType{t_Namespace}; }
  O<Value> get(uz i) override {
    throw std::runtime_error(
        "CXBQN: can only index into builtin namespace with strings");
  }
  O<Value> set(bool should_be_set, const std::string &n, O<Value> v) override {
    throw std::runtime_error("CXBQN: builtin namespaces are immutable");
  }
  O<Value> set(bool should_be_set, uz n, O<Value> v) override {
    throw std::runtime_error("CXBQN: builtin namespaces are immutable");
  }
};

struct VarAlias : public Value {
  O<Namespace> _ns;
  std::string _name;
  VarAlias(O<Value> ns, std::string n)
      : _ns{dyncast<Namespace>(ns)}, _name{n} {}
  TypeType t() const override { return TypeType{annot(t_Alias)}; }
  std::ostream &repr(std::ostream &os) const override {
    return os << "( alias " << _name << ")";
  }
  O<Value> set(bool should_be_set, O<Value> v);
};

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
inline auto type_builtin(const O<Value> v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}

} // namespace types
} // namespace cxbqn
