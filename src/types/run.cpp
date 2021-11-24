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

  auto cu = make_shared<CompUnit>();

  auto bqnbc = ARR(comparr->values[0])->values;
  for (auto v : bqnbc)
    cu->_bc.push_back(NUM(v)->v);

  cu->_consts = ARR(comparr->values[1]);

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

  std::vector<std::string> namelist;
  auto bqnbodies = ARR(comparr->values[3]);
  for (auto v : bqnbodies->values) {
    auto bod = ARR(v);
    const auto offset = static_cast<uz>(NUM(bod->values[0])->v);
    const auto varcnt = static_cast<uz>(NUM(bod->values[1])->v);

    Body b{offset, varcnt};

    const auto name_idxs = ARR(bod->values[2]);
    const auto mask = ARR(bod->values[3]);
    {
      const auto tok_info = ARR(comparr->values[5]);
      const auto tmp = ARR(tok_info->values[2]);
      const auto _namelist = ARR(tmp->values[0]);
      namelist.resize(_namelist->N());
      for(uz i=0; i<_namelist->N(); i++) {
        auto s = ARR(_namelist->values[i])->to_string();
        namelist[i] = s;
        cu->_exported.insert({s, i});
      }
    }
    for(auto& [k,v]:cu->_exported)
      fmt::print("{}->{}\n",k,v);
    for(int i=0; i < namelist.size(); i++)
      fmt::print("{}->{}\n",i,namelist[i]);

    cu->_bodies.push_back(b);
  }

  for (auto &blkd : blk_defs)
    cu->_blocks.emplace_back(blkd);

  RunResult ret;

  ret.scp = make_shared<Scope>(cu);
  auto body = cu->_bodies[cu->_blocks[0].body_idx(0)];
  ret.scp->vars.resize(body.var_count);
  ret.scp->names = namelist;

  ret.v = vm::vm(cu, ret.scp, body);

  return ret;
}

static bool loginit = false;
RunResult run(std::vector<i32> bc, O<Array> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> &bodies,
              std::unordered_map<std::string, uz> exported,
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
  cu->_blocks = blks;
  cu->_bodies = bodies;
  cu->_consts = consts;
  cu->_exported = exported;

  ret.scp = make_shared<Scope>(cu);
  auto body = bodies[blks[0].body_idx(0)];
  ret.scp->vars.resize(body.var_count);

  if (source_indices.has_value()) {
    if (nullptr == source)
      throw std::runtime_error(
          "vm::run: passed source indices, but source str is nullptr");
    ret.scp->set_source_info(source_indices.value(), source);
  }

  ret.v = vm::vm(cu, ret.scp, body);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  INSTR_REPORT();
  VMDEBUG_FINALIZE();

  return ret;
}

#undef INSTR
#undef INSTR1
#undef INSTR2


} // namespace cxbqn::vm
