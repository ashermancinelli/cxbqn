#pragma once
#include <cxbqn/debug.hpp>
#include <map>
#include <spdlog/fmt/bundled/color.h>
#include <string>

namespace cxbqn {

#ifdef CXBQN_PROFILE_VM
static std::map<std::string, uz> instr_counts;
#define INCR_INSTR(x) instr_counts[x]++;
#define INSTR_REPORT()                                                         \
  do {                                                                         \
    const auto tot =                                                           \
        std::accumulate(instr_counts.begin(), instr_counts.end(), 0,           \
                        [](auto acc, auto kv) { return acc + kv.second; });    \
    std::vector<std::pair<std::string, uz>> freq;                              \
    for (const auto it : instr_counts)                                         \
      freq.push_back(it);                                                      \
    std::sort(freq.begin(), freq.end(),                                        \
              [](auto a, auto b) { return a.second > b.second; });             \
    fmt::print("{:^30}{:<20}{:<20}\n", "instruction", "count", "\% of total"); \
    for (const auto &[k, v] : freq) {                                          \
      fmt::print("{:^30}{:<20}{:<2.5f}\n", k, v, 100.0 * ((f64)v / tot));      \
    }                                                                          \
  } while (0);
#else
#define INCR_INSTR(...) (void)0
#define INSTR_REPORT() (void)0
#endif

#ifdef CXBQN_DEBUG_VM

#ifdef CXBQN_COLOR
#define INSTR_CL (fmt::fg(fmt::color::cyan)),
#define PC_CL (fmt::fg(fmt::color::light_green)),
#define ARG_CL (fmt::fg(fmt::color::yellow)),
#define EVAL_CL (fmt::fg(fmt::color::orange)),
#define STK_CL (fmt::fg(fmt::color::light_coral)),
#else
#define INSTR_CL
#define PC_CL
#define ARG_CL
#define EVAL_CL
#define STK_CL
#endif

static const char *vm_out_filename = "cxbqn-vm.log";
static std::FILE *vm_out = nullptr;

// Print the program counter
#define INSTR_PC(pc) fmt::print(vm_out, PC_CL "@{:<4}", pc)

// Print the instruction
#define INSTR_INSTR(x) fmt::print(vm_out, INSTR_CL "{}", x)

// Print the stack
#define P_STK()                                                                \
  do {                                                                         \
    std::stringstream ss;                                                      \
    for (int i = 0; i < stk.size(); i++) {                                     \
      ss << CXBQN_STR_NC(stk[i]);                                              \
      if (i + 1 < stk.size())                                                  \
        ss << "; ";                                                            \
    }                                                                          \
    fmt::print(vm_out, STK_CL "  {}", ss.str());                               \
  } while (0);

// Indent according to the level of nesting in the given vm execution
static cxbqn::u8 indent;
#define VMDEBUG_INIT()                                                         \
  indent = -1;                                                                 \
  vm_out = fopen(vm_out_filename, "a");
#define VMDEBUG_FINALIZE() fclose(vm_out);

#define INDENT()                                                               \
  for (int i = 0; i < indent; i++)                                             \
    fmt::print(vm_out, "    ");

#define INSTR(x)                                                               \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    fmt::print(vm_out, "{:<6}", "");                                           \
    P_STK();                                                                   \
    fmt::print(vm_out, "\n");                                                  \
  } while (0);
#define INSTR1(x)                                                              \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    const auto s = fmt::format(" {}", bc[pc + 1]);                             \
    fmt::print(vm_out, ARG_CL "{:<6}", s);                                     \
    P_STK();                                                                   \
    fmt::print(vm_out, "\n");                                                  \
  } while (0);
#define INSTR2(x)                                                              \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    const auto s = fmt::format(" {} {}", bc[pc + 1], bc[pc + 2]);              \
    fmt::print(vm_out, ARG_CL "{:<6}", s);                                     \
    P_STK();                                                                   \
    fmt::print(vm_out, "\n");                                                  \
  } while (0);

#define CXBQN_NEWEVAL()                                                        \
  do {                                                                         \
    indent++;                                                                  \
    INDENT();                                                                  \
    fmt::print(vm_out, EVAL_CL "     {}\n", "new eval");                       \
  } while (0);

#define CXBQN_ENDEVAL()                                                        \
  do {                                                                         \
    INDENT();                                                                  \
    fmt::print(vm_out, EVAL_CL "     {}\n", "end eval");                       \
    indent--;                                                                  \
  } while (0);

#else
#define CXBQN_NEWEVAL(...) (void)0
#define CXBQN_ENDEVAL(...) (void)0
#define VMDEBUG_INIT(...) (void)0
#define VMDEBUG_FINALIZE(...) (void)0
#define INSTR(...) (void)0
#define INSTR1(...) (void)0
#define INSTR2(...) (void)0
#endif

} // namespace cxbqn
