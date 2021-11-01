#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <spdlog/fmt/bundled/color.h>
#include <sstream>

#ifdef CXBQN_DEBUG_VM

#ifdef CXBQN_COLOR
#define INSTR_CL (fmt::fg(fmt::color::cyan)),
#define PC_CL (fmt::fg(fmt::color::light_green)),
#define ARG_CL (fmt::fg(fmt::color::yellow)),
#define EVAL_CL (fmt::fg(fmt::color::orange)),
#else
#define INSTR_CL
#define PC_CL
#define ARG_CL
#define EVAL_CL
#endif

#define INSTR_PC(pc) fmt::print(PC_CL "@{:<4}", pc)
#define INSTR_INSTR(x) fmt::print(INSTR_CL "{}", x)

static cxbqn::u8 indent = -1;
#define INDENT()                                                              \
  for (int i = 0; i < indent; i++)                                                  \
    fmt::print("    ");

#define INSTR(x)                                                               \
  do {                                                                         \
    INSTR_PC(pc);                                                              \
    INDENT();                                                            \
    INSTR_INSTR(x);                                                            \
    fmt::print("\n");                                                          \
  } while (0);
#define INSTR1(x)                                                              \
  do {                                                                         \
    INSTR_PC(pc);                                                              \
    INDENT();                                                            \
    INSTR_INSTR(x);                                                            \
    fmt::print(ARG_CL " {}\n", bc[pc + 1]);                                    \
  } while (0);
#define INSTR2(x)                                                              \
  do {                                                                         \
    INSTR_PC(pc);                                                              \
    INDENT();                                                            \
    INSTR_INSTR(x);                                                            \
    fmt::print(ARG_CL " {}, {}\n", bc[pc + 1], bc[pc + 2]);                    \
  } while (0);

#define CXBQN_NEWEVAL() \
  do { \
    indent++; \
    INDENT();                                                            \
    fmt::print(EVAL_CL "     {}\n", "new eval"); \
  } while(0);

#define CXBQN_ENDEVAL() \
  do { \
    INDENT();                                                            \
    fmt::print(EVAL_CL "     {}\n", "end eval"); \
    indent--; \
  } while(0);

#else
#define CXBQN_NEWEVAL(...)
#define CXBQN_ENDEVAL(...)
#define INSTR(...)
#define INSTR1(...)
#define INSTR2(...)
#endif

namespace cxbqn::vm {

using namespace types;

RunResult run(std::vector<i32> bc, std::vector<Value *> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> bodies) {

  CXBQN_SETLOGSTR();
  CXBQN_DEBUG("vm::run");
  CXBQN_DEBUG("bc={}", ByteCodeRef(bc));

#ifdef CXBQN_DEEPCHECKS
  for (const auto &b : bodies)
    CXBQN_DEBUG("{}", b);
#endif

  std::vector<Block> blks;

  for (auto &blkd : blk_defs)
    blks.emplace_back(bc, blkd, bodies);

  CXBQN_DEBUG("blocks={}", std::span(blks));

  std::deque<Value *> stk;

  RunResult ret;

  ret.scp = new Scope(nullptr, blks, 0, consts);

  std::copy_n(consts.begin(), consts.size(), ret.scp->vars.begin());

  ret.v = vm::vm(bc, consts, stk, ret.scp);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  return ret;
}

Value *vm(ByteCodeRef bc, std::span<Value *> consts, std::deque<Value *> stk,
          Scope *scope) {

  CXBQN_NEWEVAL();

  CXBQN_DEBUG("bc={},consts={}", bc, consts);

  // program counter
  uz pc = 0;

  Value* ret=nullptr;

  CXBQN_DEBUG("enter interpreter loop");
  while (1) {
    CXBQN_INFO("bc={},pc={},stack={},scope={}", bc[pc], pc, stk, *scope);
    switch (bc[pc]) {
    case op::PUSH:
      INSTR1("PUSH");
      stk.push_back(consts[bc[++pc]]);
      break;
    case op::RETN:
      INSTR("RETN");
      CXBQN_DEBUG_NC("returning {}", stk.back());
      ret = stk.back();
      goto done;
      break;
    case op::POPS:
      INSTR("POPS");
      stk.pop_back();
      break;
    case op::VARM:
      INSTR2("VARM");
      instructions::varm(bc, pc, stk);
      break;
    case op::SETN:
      INSTR("SETN");
      instructions::setn(stk, scope);
      break;
    case op::SETU:
      INSTR("SETU");
      instructions::setu(stk, scope);
      break;
    case op::VARO:
    case op::VARU:
      INSTR2("VARO/VARU");
      instructions::varo(bc, pc, stk, scope);
      break;
    case op::FN1O:
    case op::FN1C:
      INSTR("FN10/FN1C");
      instructions::fn10(bc, pc, stk);
      break;
    case op::FN2O:
    case op::FN2C:
      INSTR("FN20/FN2C");
      instructions::fn20(bc, pc, stk);
      break;
    case op::DFND:
      INSTR1("DFND");
      instructions::dfnd(bc, pc, stk, scope);
      break;
    case op::ARRO:
      INSTR1("ARRO");
      instructions::arro(bc, pc, stk);
      break;
    case op::ARRM:
      INSTR1("ARRM");
      instructions::arrm(bc, pc, stk);
      break;
    case op::MD1C:
      INSTR("MD1C");
      instructions::md1c(bc, pc, stk, scope);
      break;
    default:
      CXBQN_CRIT("unreachable code {}", bc[pc]);
      throw std::runtime_error("vm::vm: unreachable code");
    }
    pc++;
  }

done:

  CXBQN_ENDEVAL();

  return ret;
}

#undef INSTR
#undef INSTR1
#undef INSTR2

} // namespace cxbqn::vm
