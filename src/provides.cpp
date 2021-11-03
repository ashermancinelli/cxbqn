#include <cxbqn/provides.hpp>
#include <cxbqn/debug.hpp>

namespace cxbqn::provides {

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type,
// and we want that converted into a Value*.
static inline Number* type_builtin(const Value* v) {
  return new Number(static_cast<f64>((v->t() & TypeType{0b111}).to_ulong()));
}

Value *Type::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("•Type::call:nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Type does not have a dyadic definition");
#ifdef CXBQN_DEEPCHECKS
  if (args.size() < 2)
    throw std::runtime_error("type got <2 args");
  if (nullptr == /*𝕩=*/args[1])
    throw std::runtime_error("type got nullptr for 𝕩");
#endif
  return type_builtin(args[1]);
}

// Value *Type::call(u8 nargs, std::vector<Value *> args) { }

} // namespace cxbqn::provides
