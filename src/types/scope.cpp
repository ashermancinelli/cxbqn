#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

O<Scope> Scope::root_scope(O<CompUnit> cu, std::vector<Block> blks, ByteCode bytecode,
                           std::vector<Body> bods,
                           O<std::unordered_map<std::string, uz>> exported) {
  auto scp = make_shared<Scope>(cu, 0, true);
  scp->_bods = bods;
  scp->_bc = bytecode;
  scp->_blks = blks;
  scp->_exported = exported;
  scp->vars.resize(8 + blks[scp->blk_idx].max_nvars(bods));
  std::fill(scp->vars.begin(), scp->vars.end(), nullptr);
  return scp;
}

O<Scope> Scope::child_scope(W<Scope> parent, uz blk_idx, uz nvars) {
  auto p = parent.lock();
  auto scp = make_shared<Scope>(p->cu, blk_idx, false);
  scp->parent = parent;
  scp->_exported = p->_exported;
  scp->vars.resize(nvars);
  std::fill(scp->vars.begin(), scp->vars.end(), nullptr);
  return scp;
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
  return _blks.has_value() ? _blks.value() : parent.lock()->blocks();
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

void Scope::set(bool should_var_be_set, O<Reference> r, O<Value> _v) {

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == _v)
    throw std::runtime_error("assign: got nullptr value");
#endif

  // fmt::print("ref.tag={}\n",(r->tag.has_value()?r->tag.value():"none"));

  O<Value> v = _v;
  if (r->tag.has_value()) {
    fmt::print("tag={}\n", r->tag.value());
    auto ns = dynamic_pointer_cast<Namespace>(_v);
    auto n = r->tag.value();
    v = ns->get(n);
  }

  if (t_Namespace == type_builtin(_v)) {
    fmt::print("scope:ns\n");
  }

  const auto n = r->depth;
  CXBQN_DEBUG("Scope::set:shoudbeset={},depth={}", should_var_be_set, n);
  auto scp = get_nth_parent(n);
  CXBQN_DEBUG_NC("Scope::set:nth parent={}", scp);

  CXBQN_DEBUG("Scope::set:r->pos={},scp->vars={}", r->position_in_parent,
              scp->vars);

  if (r->position_in_parent > scp->vars.size())
    scp->vars.resize(1 + r->position_in_parent);

  bool isset = !(nullptr == scp->vars[r->position_in_parent] or
                 scp->vars[r->position_in_parent]->t()[t_Nothing]);
  if (should_var_be_set != isset) {
    CXBQN_CRIT("should_var_be_set={},isset={},scp->vars={}", should_var_be_set,
               isset, scp->vars);
    throw std::runtime_error(
        "Expected var to be set or unset, but this was not the case");
  }

  // fmt::print("{} = {}\n", CXBQN_STR_NC(scp->vars[r->position_in_parent]),
  // CXBQN_STR_NC(v)); assign to the underlying value
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

const std::pair<std::vector<uz>, std::vector<uz>> &
Scope::source_indices() const {
#ifdef CXBQN_DEEPCHECKS
  if (!_source_indices.has_value() and nullptr == parent.lock())
    throw std::runtime_error("expected to have source indices or a parent");
#endif
  return _source_indices.has_value() ? _source_indices.value()
                                     : parent.lock()->source_indices();
}

const std::string_view Scope::source_str() const {
#ifdef CXBQN_DEEPCHECKS
  if (!_source_indices.has_value() and nullptr == parent.lock())
    throw std::runtime_error("expected to have source indices or a parent");
#endif
  return _source_str.has_value() ? _source_str.value()
                                 : parent.lock()->source_str();
}

void Scope::set_source_info(std::vector<std::vector<uz>> si, O<Array> s) {
  CXBQN_DEBUG("Scope::set_source_info");
  if (si.size() != 2)
    throw std::runtime_error("source indices can only have two values");

  // Break the source info into a pair
  _source_indices = std::pair(si[0], si[1]);

  // create a standard string of the source text
  std::string _s;
  for (auto v : s->values)
    utf8::append(dynamic_pointer_cast<Character>(v)->c(),
                 std::back_inserter(_s));
  _source_str = _s;
}

void Scope::source_for_program_counter(uz pc, std::stringstream &ss) const {
  const auto &si = source_indices();
  const auto b = si.first[pc], e = si.second[pc];
  const auto s = source_str();
  auto it_start = s.begin();
  utf8::advance(it_start, b, s.end());
  auto it_end = it_start;
  utf8::advance(it_end, 1 + (e - b), s.end());

  /*
   * We will look this many chars ahead and behind to look for a line break.
   * If found, we'll use that as our bounds for the source that we print in our
   * stack trace.
   */
  static constexpr uz nlookahead = 50;

  for (int i = 0; i < nlookahead and it_end != s.end();
       i++, utf8::next(it_end, s.end()))
    if (*it_end == '\n')
      break;

  // Keep this variable around so we can point to the char in question
  int dis;
  for (dis = 0; dis < nlookahead and it_start != s.begin();
       dis++, utf8::prior(it_start, s.begin()))
    if (*it_start == '\n')
      break;

  std::string sfinal(it_start, it_end);
  ss << sfinal << "\n";
  for (int i = 0; i < dis; i++)
    ss << "·";
  ss << "∧\n";
}

} // namespace cxbqn::types
