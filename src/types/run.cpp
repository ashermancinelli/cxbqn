#include "vm_macros.hpp"
#include <cxbqn/cxbqn.hpp>
#include <sstream>

namespace cxbqn::vm {

using namespace types;

#define ARR(x) dyncast<ArrayBase>(x)
#define NUM(x) dyncast<Number>(x)

observer_ptr<CompUnit> deconstruct(O<Value> compiled) {
  auto comparr = ARR(compiled);

  auto cu = make_observer(new CompUnit());

  auto bqnbc = ARR(comparr->get(0));
  for (int i=0; i<bqnbc->N(); i++)
    cu->_bc.push_back(NUM(bqnbc->get(i))->v);

  cu->_consts = dyncast<Array>(comparr->get(1));

  std::vector<BlockDef> blk_defs;
  auto bqnblks = dyncast<Array>(comparr->get(2));
  for (int blki=0; blki<bqnblks->N(); blki++) {
    auto vv = dyncast<Array>(bqnblks->get(blki));
    auto type = static_cast<uz>(NUM(vv->get(0))->v);
    auto imm = static_cast<uz>(NUM(vv->get(1))->v);

    if (auto ambiv_idx = NUM(vv->get(2))) {
      blk_defs.push_back(BlockDef{type, imm, static_cast<uz>(ambiv_idx->v)});
    } else {
      auto body_idxs = ARR(vv->get(2));
      auto mon = ARR(body_idxs->get(0));
      auto dya = ARR(body_idxs->get(1));
      std::vector<uz> moni, dyai;

      for (int i=0; i<mon->N(); i++)
        moni.push_back(static_cast<uz>(NUM(mon->get(i))->v));
      for (int i=0; i<dya->N(); i++)
        moni.push_back(static_cast<uz>(NUM(dya->get(i))->v));

      const auto bods = std::vector<std::vector<uz>>{moni, dyai};
      blk_defs.push_back(BlockDef{type, imm, bods});
    }
  }

  auto bqnbodies = ARR(comparr->get(3));
  for (int bodi=0; bodi < bqnbodies->N(); bodi++) {
    auto bod = ARR(bqnbodies->get(bodi));
    const auto offset = static_cast<uz>(NUM(bod->get(0))->v);
    const auto varcnt = static_cast<uz>(NUM(bod->get(1))->v);

    Body b{offset, varcnt};

    const auto name_idxs = ARR(bod->get(2));
    const auto mask = ARR(bod->get(3));
    {
      const auto tok_info = ARR(comparr->get(5));
      const auto tmp = ARR(tok_info->get(2));
      const auto _namelist = ARR(tmp->get(0));
      cu->_namelist.resize(_namelist->N());
      for (uz i = 0; i < _namelist->N(); i++) {
        auto n = _namelist->get(i);
        auto s = to_string(n);
        cu->_namelist[i] = s;
        cu->_exported.insert({s, i});
      }
    }

    cu->_bodies.push_back(b);
  }

  for (auto &blkd : blk_defs)
    cu->_blocks.emplace_back(blkd);

  return cu;
}

RunResult run(observer_ptr<CompUnit> cu) {
  RunResult ret;

  ret.scp = make_observer(new Scope(cu));
  auto body = cu->_bodies[cu->_blocks[0].body_idx(0)];
  ret.scp->vars.resize(body.var_count);
  ret.scp->names = cu->_namelist;

  ret.v = vm::vm(cu, ret.scp, body);

  return ret;
}

RunResult run(O<Value> compiled) {
  auto cu = deconstruct(compiled);
  return run(cu);
}

static bool loginit = false;
RunResult run(std::vector<i32> bc, O<ArrayBase> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> &bodies,
              std::unordered_map<std::string, uz> exported,
              std::optional<std::vector<std::vector<uz>>> source_indices,
              O<ArrayBase> source) {

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

  auto cu = make_observer(new CompUnit());
  cu->_bc = bc;
  cu->_blocks = blks;
  cu->_bodies = bodies;
  cu->_consts = dyncast<Array>(consts);
  cu->_exported = exported;

  ret.scp = make_observer(new Scope(cu));
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
