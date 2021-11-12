#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

O<Scope> Scope::root_scope(std::vector<Block> blks, ByteCode bytecode,
                           std::vector<O<Value>> consts, std::vector<Body> bods) {
  auto scp = make_shared<Scope>(0);
  scp->_bods = bods;
  scp->_bc = bytecode;
  scp->_consts = consts;
  scp->_blks = blks;
  scp->vars.resize(6 + blks[scp->blk_idx].max_nvars(bods));
  return scp;
}

O<Scope> Scope::child_scope(W<Scope> parent, uz blk_idx) {
  auto scp = make_shared<Scope>(blk_idx);
  scp->parent = parent;
  scp->vars.resize(6 + scp->blocks()[scp->blk_idx].max_nvars(scp->bodies()));
  return scp;
}

std::vector<O<Value>> Scope::consts() const {
#ifdef CXBQN_DEEPCHECKS
  if (nullopt == _consts and 0 == parent.use_count())
    throw std::runtime_error("scope: expected to either own consts or to have "
                             "parent, but neither is the case.");
#endif
  return _consts.has_value() ? _consts.value() : parent.lock()->consts();
}

std::span<const Body> Scope::bodies() const {
#ifdef CXBQN_DEEPCHECKS
  if (nullopt == _bods and 0 == parent.use_count())
    throw std::runtime_error("scope: expected to either own blocks or to have "
                             "parent, but neither is the case.");
#endif
  return _bods.has_value() ? _bods.value() : parent.lock()->bodies(); 
}

std::span<const Block> Scope::blocks() const {
#ifdef CXBQN_DEEPCHECKS
  if (nullopt == _blks and 0 == parent.use_count())
    throw std::runtime_error("scope: expected to either own blocks or to have "
                             "parent, but neither is the case.");
#endif
  // return _blks.has_value() ? _blks.value() : parent.lock()->blocks(); 
  if (_blks.has_value()) 
    return std::span(_blks.value().begin(), _blks.value().size());
  return parent.lock()->blocks();
    // ? _blks.value() : parent.lock()->blocks(); 
}

const ByteCodeRef Scope::bc() const {
#ifdef CXBQN_DEEPCHECKS
  if (0 == parent.use_count() and !_bc.has_value())
    throw std::runtime_error("scope: expected to either own bc or to have "
                             "parent, but neither is the case.");
#endif
  return _bc.has_value() ? _bc.value() : parent.lock()->bc();
}

O<Value> Scope::get(O<Reference> r) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("Scope::get got nullptr reference");
#endif

  const auto n = r->depth;
  O<Scope> scp = get_nth_parent(n);

  return scp->vars[r->position_in_parent];
}

void Scope::set(bool should_var_be_set, O<Reference> r, O<Value> v) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == v)
    throw std::runtime_error("assign: got nullptr value");
#endif

  const auto n = r->depth;
  CXBQN_DEBUG("Scope::set:shoudbeset={},depth={}", should_var_be_set, n);
  auto scp = get_nth_parent(n);
  CXBQN_DEBUG_NC("Scope::set:nth parent={}", scp);

  CXBQN_DEBUG("Scope::set:r->pos={},scp->vars={}", r->position_in_parent,
              scp->vars);

  bool isset = nullptr != scp->vars[r->position_in_parent];
  if (should_var_be_set != isset) {
    CXBQN_CRIT("should_var_be_set={},isset={}", should_var_be_set, isset);
    throw std::runtime_error(
        "Expected var to be set or unset, but this was not the case");
  }

  // assign to the underlying value
  scp->vars[r->position_in_parent] = v;
}

O<Scope> Scope::get_nth_parent(uz depth) {
  CXBQN_DEBUG("Scope::get_nth_parent:depth={}", depth);
  auto scp = shared_from_this();
  while (depth-- > 0) {
    CXBQN_DEBUG("Scope::get_nth_parent:traversing to parent. depth={}", depth);
    CXBQN_DEBUG_NC("before={}", scp);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp->parent.lock())
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
    scp = scp->parent.lock();
    CXBQN_DEBUG_NC("after={}", scp);
  }
  return scp;
}

} // namespace cxbqn::types
