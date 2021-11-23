#include <cxbqn/comp_unit.hpp>

namespace cxbqn::types {

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
O<CompUnit> CompUnit::from_raw(O<Value> compiled) {

  auto cu = make_shared<CompUnit>();

  auto comparr = ARR(compiled);

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

  auto exported = make_shared<std::unordered_map<std::string, uz>>();

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
    // for(auto& [k,v]:*exported)
      // fmt::print("{}->{}\n",k,v);

    cu->_bods.push_back(b);
  }

  for (auto &blkd : blk_defs)
    cu->_blks.emplace_back(blkd);

  return cu;
}

#if 0
O<CompUnit> CompUnit::from_raw(CompileParams& p) {
  auto ret = make_shared<CompUnit>();

  ret->bc = p.bc;

  ret->consts = p.v;

  auto bodies = p.bodies;

  auto bqnbodies = ARR(comparr->values[3]);
  for (auto v : bqnbodies->values) {
    auto bod = ARR(v);
    const auto offset = static_cast<uz>(NUM(bod->values[0])->v);
    const auto varcnt = static_cast<uz>(NUM(bod->values[1])->v);

    const auto _name_idxs = ARR(bod->values[2]);
    std::vector<uz> name_idxs;
    for(auto e : _name_idxs->values)
      name_idxs.push_back(NUM(e)->v);

    const auto _mask = ARR(bod->values[3]);
    std::vector<u8> mask;
    for (auto e : _mask)
      mask.push_back(NUM(e)->v);

    bodies.push_back(Body(offset, varcnt, name_idxs, mask));
  }

  auto bqnblks = ARR(comparr->values[2]);
  for (auto v : bqnblks->values) {
    auto vv = ARR(v);
    auto type = static_cast<uz>(NUM(vv->values[0])->v);
    auto imm = static_cast<uz>(NUM(vv->values[1])->v);

    if (auto ambiv_idx = NUM(vv->values[2])) {
      ret->blocks.push_back(Block{type, imm, bodies[static_cast<uz>(ambiv_idx->v)]});
    } else {
      auto body_idxs = ARR(vv->values[2]);
      auto _mon = ARR(body_idxs->values[0]);
      auto _dya = ARR(body_idxs->values[1]);
      std::vector<O<Body>> mon, dya;

      for (auto i : _mon->values)
        moni.push_back(bodies[static_cast<uz>(NUM(i)->v)]);
      for (auto i : _dya->values)
        dyai.push_back(bodies[static_cast<uz>(NUM(i)->v)]);

      ret->blocks.push_back(Block{type, imm, mon, dya});
    }
  }

  return ret;
}
#endif

} // namespace cxbqn::types
