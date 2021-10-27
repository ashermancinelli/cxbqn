#include <cxbqn.hpp>
#include <deque>
#include <spdlog/spdlog.h>
#include <sstream>

namespace cxbqn::vm {

template <typename BcType, typename StackType>
u64 _num(std::vector<BcType> &bc, uz &prog_counter, StackType &stack) {
  static constexpr u64 b{128};
  u64 n = bc[prog_counter++];
  if (n < b)
    return n;

  // wtf is this
  u64 i{1}, t{0};
  do {
    t += i * (n - b);
    i *= b;
    n = bc[prog_counter++];
  } while (n >= b);

  return t + i * n;
}

namespace {

template <typename ValueContainer>
void vdbg(const char *label, ValueContainer c) {
  using namespace cxbqn::fmt;
  std::stringstream ss;
  ss << label << ":[";
  for (const auto e : c) {
    fmt::repr(ss, e);
    ss << ",";
  }
  ss << "]";
  spdlog::debug("{}", ss.str());
}

template <typename ValueContainer>
void dbg(const char *label, ValueContainer c) {
  using namespace cxbqn::fmt;
  std::stringstream ss;
  ss << label << ":[";
  for (const auto e : c) {
    ss << e << ",";
  }
  ss << "]";
  spdlog::debug("{}", ss.str());
}

} // namespace

Value* vm(std::vector<i32> bc, std::vector<Value *> consts, std::vector<Block> blks,
      std::vector<Body> bodies, std::deque<Value*> stk) {
  spdlog::set_pattern("cxbqn:vm:vm[%^%l%$] %v");
  spdlog::debug("enter vm");

  dbg("bc", bc);
  dbg("blocks", blks);
  dbg("bodies", bodies);

  // program counter
  uz pc = 0;

  // this is very expensive
  vdbg("consts", consts);

  types::Value* v;
  types::Number* n;

  spdlog::debug("enter interpreter loop");
  while (1) {
    spdlog::debug("bc={},pc={}", bc[pc], pc);
    // vdbg("stack", stk);
    switch (bc[pc]) {
    case op::PUSH:
      pc++;
      spdlog::debug("op:PUSH bc[pc++]={}", bc[pc]);
      stk.push_back(consts[bc[pc]]);
      break;
    case op::RETN:
      spdlog::debug("op:RETN");
      return stk.back();
      break;
    case op::POPS:
      stk.pop_back();
      break;
    case op::VARM:
      break;
    case op::SETN:
      break;
    default:
      spdlog::critical("unreachable code {}", bc[pc]);
      throw std::runtime_error("cxbqn::vim::vim: unreachable code");
    }
    pc++;
  }

  return 0;
}

} // namespace cxbqn::vm
