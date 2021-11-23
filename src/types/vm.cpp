#include "vm_macros.hpp"
#include <cxbqn/cxbqn.hpp>
#include <sstream>

namespace cxbqn::vm {

using namespace types;

#define ARR(x) dynamic_pointer_cast<Array>(x)
#define NUM(x) dynamic_pointer_cast<Number>(x)

/*
Example compiled output of "5+5":

⟨sh=⟨6⟩

  0. bytecode
  ⟨sh=⟨8⟩0,1,0,0,0,1,17,7⟩,

  1. consts
  ⟨sh=⟨2⟩
    ( md2D ( md2D + Block{i=7} (fork f=0,g==,h=•Type)) Block{i=10} ⟨sh=⟨3⟩+,(
md2D ( md2D Block{i=167} ⊘ ( md2D ( md2D (fork f=1,g=-,h=≤) Block{i=7} (fork
f=0,g==,h=•Type)) Block{i=10} ⟨sh=⟨2⟩Block{i=165},Block{i=166}⟩)) _fillBy_
Block{i=164}),( md2D Block{i=169} _fillBy_ Block{i=168})⟩), 5⟩,

  2. blocks
  ⟨sh=⟨1⟩⟨sh=⟨3⟩0,1,0⟩⟩,

  3. bodies
  ⟨sh=⟨1⟩⟨sh=⟨4⟩0,0,⟨sh=⟨0⟩⟩,⟨sh=⟨0⟩⟩⟩⟩,

  4. error reporting stuff
  ⟨sh=⟨2⟩
    ⟨sh=⟨8⟩2,2,1,1,0,0,1,0⟩,⟨sh=⟨8⟩2,2,1,1,0,0,1,0⟩⟩,
    ⟨sh=⟨5⟩⟨sh=⟨3⟩92,0,92⟩,⟨sh=⟨3⟩0,1,0⟩,⟨sh=⟨5⟩⟨sh=⟨0⟩⟩,⟨sh=⟨0⟩⟩,⟨sh=⟨1⟩5⟩,⟨sh=⟨0⟩⟩,⟨sh=⟨0⟩⟩⟩,⟨sh=⟨3⟩0,1,2⟩,⟨sh=⟨3⟩0,1,2⟩⟩⟩
      */

RunResult run(O<Value> compiled) {
  auto comparr = ARR(compiled);

  std::vector<i32> bc;
  auto bqnbc = ARR(comparr->values[0])->values;
  for (auto v : bqnbc)
    bc.push_back(NUM(v)->v);

  auto consts = ARR(comparr->values[1]);

  std::vector<BlockDef> blk_defs;
  auto bqnblks = ARR(comparr->values[2]);
  for (auto v : bqnblks->values) {
    auto vv = ARR(v);
    auto type = static_cast<uz>(NUM(vv->values[0])->v);
    auto imm = static_cast<uz>(NUM(vv->values[1])->v);

    if (auto ambiv_idx = NUM(vv->values[2])) {
      blk_defs.push_back(BlockDef{type, imm, static_cast<uz>(ambiv_idx->v)});
    } else {
      auto body_idxs = ARR(vv->values[2]);
      auto mon = ARR(body_idxs->values[0]);
      auto dya = ARR(body_idxs->values[1]);
      std::vector<uz> moni, dyai;

      for (auto i : mon->values)
        moni.push_back(static_cast<uz>(NUM(i)->v));
      for (auto i : dya->values)
        dyai.push_back(static_cast<uz>(NUM(i)->v));

      const auto bods = std::vector<std::vector<uz>>{moni, dyai};
      blk_defs.push_back(BlockDef{type, imm, bods});
    }
  }

  auto exported = make_shared<std::unordered_map<std::string, uz>>();

  std::vector<Body> bodies;
  auto bqnbodies = ARR(comparr->values[3]);
  for (auto v : bqnbodies->values) {
    auto bod = ARR(v);
    const auto offset = static_cast<uz>(NUM(bod->values[0])->v);
    const auto varcnt = static_cast<uz>(NUM(bod->values[1])->v);

    Body b{offset, varcnt};

    const auto name_idxs = ARR(bod->values[2]);
    const auto mask = ARR(bod->values[3]);
    std::vector<std::string> namelist;
    {
      const auto tok_info = ARR(comparr->values[5]);
      const auto tmp = ARR(tok_info->values[2]);
      const auto _namelist = ARR(tmp->values[0]);
      for(uz i=0; i<_namelist->N(); i++)
        exported->insert({ARR(_namelist->values[i])->to_string(), i});
    }
    for(auto& [k,v]:*exported)
      fmt::print("{}->{}\n",k,v);

    bodies.push_back(b);
  }

  return vm::run(bc, consts, blk_defs, bodies, exported);
}

static bool loginit = false;
RunResult run(std::vector<i32> bc, O<Array> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> &bodies,
              O<std::unordered_map<std::string, uz>> exported,
              std::optional<std::vector<std::vector<uz>>> source_indices,
              O<Array> source) {

  if (!loginit) {
    CXBQN_SETLOGSTR();
    loginit = true;
  }

  CXBQN_DEBUG("vm::run");
  CXBQN_DEBUG("bc={}", ByteCodeRef(bc));
  VMDEBUG_INIT();

#ifdef CXBQN_DEEPCHECKS
  for (const auto &b : bodies)
    CXBQN_DEBUG("{}", b);
#endif

  std::vector<Block> blks;

  for (auto &blkd : blk_defs)
    blks.emplace_back(blkd);

  CXBQN_DEBUG("blocks={}", std::span(blks));

  std::vector<O<Value>> stk;

  RunResult ret;

  auto cu = make_shared<CompUnit>();
  cu->_bc= bc;
  cu->_blks = blks;
  cu->_bods = bodies;
  cu->_consts = consts;

  ret.scp = Scope::root_scope(cu, blks, bc, bodies, exported);

  if (source_indices.has_value()) {
    if (nullptr == source)
      throw std::runtime_error(
          "vm::run: passed source indices, but source str is nullptr");
    ret.scp->set_source_info(source_indices.value(), source);
  }

  ret.v = vm::vm(cu, bc, consts, stk, ret.scp);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  INSTR_REPORT();
  VMDEBUG_FINALIZE();

  return ret;
}

static u64 iii = 0;
O<Value> vm(O<CompUnit> cu, ByteCodeRef bc, O<Array> consts, std::vector<O<Value>> stk,
            O<Scope> scope) {

  CXBQN_NEWEVAL();

  // CXBQN_DEBUG("bc={},consts={}", bc, consts);

  // program counter
  uz pc = 0;

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
        instructions::fldo(bc, pc, stk, scope->_exported);
        INSTR("FLDO");
        break;
      }
      case op::ALIM: {
        fmt::print("alim\n");
        INSTR1("ALIM");
        instructions::alim(bc, pc, stk, scope->_exported);
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
        stk.push_back(O<Value>(new Namespace(scope, scope->_exported)));
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

#undef INSTR
#undef INSTR1
#undef INSTR2

} // namespace cxbqn::vm
