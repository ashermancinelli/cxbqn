#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

  /*
static O<Scope> Scope::root_scope(std::vector<Block> blks, ByteCode bc,
                           std::vector<O<Value>> consts) {
  auto scp = make_shared<Scope>();
  scp->_bc = bc;
  scp->_consts = consts;
  scp->_blks = blks;
  scp->blk_idx = 0;
  scp->vars.resize(6 + blks[blk_idx].max_nvars());
  std::fill(scp->vars.begin(), scp->vars.end(), nullptr);
  return scp;
}

static O<Scope> Scope::child_scope(W<Scope> parent, uz blk_idx) {
  auto scp = make_shared<Scope>();
  scp->parent = parent;
  scp->blk_idx = blk_idx;
  scp->vars.resize(6 + blks[blk_idx].max_nvars());
  std::fill(scp->vars.begin(), scp->vars.end(), nullptr);
  return scp;
}
*/

Scope::Scope(Scope *parent, uz blk_idx, std::vector<Block> blks,
             std::optional<ByteCode> bc,
             std::optional<std::vector<O<Value>>> consts)
    : _blks{blks}, blk_idx{blk_idx}, _bc{bc} {
  CXBQN_DEBUG("Scope::Scope");
  this->parent = parent;
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == parent and nullopt == consts)
    throw std::runtime_error("Scope::Scope: both parent=null and consts=null");
#endif
  if (consts.has_value())
    _consts = consts.value();
  vars.resize(6 + _blks[blk_idx].max_nvars());
  std::fill(vars.begin(), vars.end(), nullptr);
}

std::vector<O<Value>> Scope::consts() const {
#ifdef CXBQN_DEEPCHECKS
  if (nullopt == _consts and nullptr == parent)
    throw std::runtime_error("scope: expected to either own consts or to have "
                             "parent, but neither is the case.");
#endif
  return _consts.has_value() ? _consts.value() : parent->consts();
}

std::span<const Block> Scope::blocks() const {
  return _blks;
}

const ByteCodeRef Scope::bc() const {
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == parent and !_bc.has_value())
    throw std::runtime_error("scope: expected to either own bc or to have "
                             "parent, but neither is the case.");
#endif
  return _bc.has_value() ? _bc.value() : parent->bc();
}

O<Value> Scope::get(O<Reference> r) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("Scope::get got nullptr reference");
#endif

  const auto n = r->depth;
  Scope *scp = get_nth_parent(n);

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
  auto *scp = get_nth_parent(n);
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

Scope *Scope::get_nth_parent(uz depth) {
  CXBQN_DEBUG("Scope::get_nth_parent:depth={}", depth);
  auto *scp = this;
  while (depth-- > 0) {
    CXBQN_DEBUG("Scope::get_nth_parent:traversing to parent. depth={}", depth);
    CXBQN_DEBUG_NC("before={}", scp);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp->parent)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
    scp = scp->parent;
    CXBQN_DEBUG_NC("after={}", scp);
  }
  return scp;
}

} // namespace cxbqn::types
