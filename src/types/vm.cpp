#include "vm_macros.hpp"
#include <cxbqn/cxbqn.hpp>
#include <sstream>

namespace cxbqn::vm {

using namespace types;

#define ARR(x) dynamic_pointer_cast<Array>(x)
#define NUM(x) dynamic_pointer_cast<Number>(x)

O<Value> vm(shared_ptr<CompUnit> cu, shared_ptr<Scope> scope, Body b) {
  uz pc = b.bc_offset;
  auto &bc = cu->_bc;
  auto &consts = cu->_consts;
  std::vector<O<Value>>stk;

  O<Value> ret = nullptr;

  CXBQN_DEBUG("enter interpreter loop");
#ifdef CXBQN_STACKTRACE
  try {
#endif
    while (1) {
#ifdef CXBQN_DEBUG_VMSTACK
      /* Logging the entire stack can severly slow the execution if logging is
       * enabled, but sometimes it's useful, so it gets its own define.
       */
      CXBQN_INFO("bc={},pc={},stack={},scope={}", bc[pc], pc, stk, *scope);
#endif
      CXBQN_LOGFLUSH();
      switch (bc[pc]) {
      case op::PRED:
      case op::SETH:
      case op::VFYM:
      case op::FLDM: {
        throw std::runtime_error("unsupported");
        break;
      }
      case op::FLDO: {
        fmt::print("fldo\n");
        INSTR1("FLDO");
        instructions::fldo(bc, pc, stk, scope->cu);
        INSTR("FLDO");
        break;
      }
      case op::ALIM: {
        fmt::print("alim\n");
        INSTR1("ALIM");
        instructions::alim(bc, pc, stk, scope->cu);
        INSTR("ALIM");
        break;
      }
      case op::PUSH: {
        INSTR1("PUSH");
        stk.push_back(consts->values[bc[++pc]]);
        INSTR("PUSH");
        break;
      }
      case op::RETN: {
        INSTR("RETN");
        CXBQN_DEBUG("returning {}", CXBQN_STR_NC(stk.back()));
        ret = stk.back();
        INSTR("RETN");
        goto done;
        break;
      }
      case op::RETD: {
        INSTR("RETD");
        stk.push_back(O<Value>(new Namespace(scope)));
        ret = stk.back();
        INSTR("RETD");
        goto done;
        break;
      }
      case op::POPS: {
        INSTR("POPS");
        stk.pop_back();
        INSTR("POPS");
        break;
      }
      case op::VARM: {
        INSTR2("VARM");
        instructions::varm(bc, pc, stk);
        INSTR("VARM");
        break;
      }
      case op::SETN: {
        INSTR("SETN");
        instructions::setn(stk, scope);
        INSTR("SETN");
        break;
      }
      case op::SETU: {
        INSTR("SETU");
        instructions::setu(stk, scope);
        INSTR("SETU");
      } break;
      case op::VARU:
      case op::VARO: {
        INSTR2("VARO");
        instructions::varo(bc, pc, stk, scope);
        INSTR("VARO");
        break;
      }
      case op::FN1C: {
        INSTR("FN1C");
        instructions::fn1c(stk);
        INSTR("FN1C");
        break;
      }
      case op::FN2C: {
        INSTR("FN2C");
        instructions::fn2c(stk);
        INSTR("FN2C");
        break;
      }
      case op::DFND: {
        INSTR1("DFND");
        instructions::dfnd(bc, pc, stk, scope, consts);
        INSTR("DFND");
        break;
      }
      case op::ARRO: {
        INSTR1("ARRO");
        instructions::arro(bc, pc, stk);
        INSTR("ARRO");
        break;
      }
      case op::ARRM: {
        INSTR1("ARRM");
        instructions::arrm(bc, pc, stk);
        INSTR("ARRM");
        break;
      }
      case op::MD1C: {
        INSTR("MD1C");
        instructions::md1c(stk);
        INSTR("MD1C");
        break;
      }
      case op::MD2C: {
        INSTR("MD2C");
        instructions::md2c(stk);
        INSTR("MD2C");
        break;
      }
      case op::TR2D: {
        INSTR("TR2D");
        instructions::tr2d(stk);
        INSTR("TR2D");
        break;
      }
      case op::TR3D: {
        INSTR("TR3D");
        instructions::tr3d(stk);
        INSTR("TR3D");
        break;
      }
      case op::TR3O: {
        INSTR("TR3D");
        instructions::tr3o(stk);
        INSTR("TR3D");
        break;
      }
      case op::SETM: {
        INSTR("SETM");
        instructions::setm(stk, scope);
        INSTR("SETM");
        break;
      }
      case op::SETC: {
        INSTR("SETC");
        instructions::setc(stk, scope);
        INSTR("SETC");
        break;
      }
      case op::FN1O: {
        INSTR("FN1O");
        instructions::fn1o(stk);
        INSTR("FN1O");
        break;
      }
      case op::FN2O: {
        INSTR("FN2O");
        instructions::fn2o(stk);
        INSTR("FN2O");
        break;
      }
      case op::CHKV: {
        INSTR("CHKV");
        if ((stk.back())->t()[t_Nothing])
          throw std::runtime_error("chkv: top of stack is ·");
        INSTR("CHKV");
        break;
      }
      default: {
        std::stringstream ss;
        ss << "vm::vm: unreachable code " << bc[pc];
        CXBQN_CRIT("{}", ss.str());
        throw std::runtime_error(ss.str());
      }
      }
      pc++;
    }
#ifdef CXBQN_STACKTRACE
  } catch (const std::runtime_error &e) {
    if (not scope->has_source_info())
      throw;
    std::stringstream ss;
    ss << e.what() << "\n";
    scope->source_for_program_counter(pc, ss);
    throw ss.str();
  }
#endif

done:

  CXBQN_ENDEVAL();

  return ret;
}

} // namespace cxbqn::vm
