#pragma once
#include <cxbqn/comp_unit.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

struct Scope : public std::enable_shared_from_this<Scope> {

  Scope(shared_ptr<CompUnit> cu) : cu{cu}, blk_idx{0} {}
  Scope(shared_ptr<Scope> parent, uz blk_idx)
      : parent{parent}, cu{parent->cu}, blk_idx{blk_idx} {}

  shared_ptr<CompUnit> cu;

  /* Get a reference by traversing the scope lineage */
  O<Value> get(O<Reference> r);

  /* Set a reference by traversing the scope lineage */
  void set(bool should_var_be_set, O<Reference> r, O<Value> v);

  /* Get the parent scope `depth` generations up. */
  shared_ptr<Scope> get_nth_parent(uz depth);

  /* When using references, we must have a way to traverse the scope lineage */
  weak_ptr<Scope> parent;

  /*
   * Each scope contains some number of variables. For functions/modifiers,
   * the first six will always be the relevant members of 𝕤𝕩𝕨𝕣𝕗𝕘.
   */
  std::vector<O<Value>> vars;
  std::vector<std::string> names;

  const uz blk_idx;

  // These are optional functions and values, only used when source locations
  // are provided.
  const std::pair<std::vector<uz>, std::vector<uz>> &source_indices() const;
  void source_for_program_counter(uz pc, std::stringstream &ss) const;
  void set_source_info(std::vector<std::vector<uz>> si, O<Array> s);
  bool has_source_info() const {
    return _source_indices.has_value() and _source_str.has_value();
  }
  const std::string_view source_str() const;
  std::optional<std::pair<std::vector<uz>, std::vector<uz>>> _source_indices =
      nullopt;
  std::optional<std::string> _source_str = nullopt;

  Scope(shared_ptr<CompUnit> cu, uz bi) : cu{cu}, blk_idx{bi}, parent{shared_ptr<Scope>{}} {}
};

} // namespace cxbqn::types
