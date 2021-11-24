#pragma once
#include <cxbqn/comp_unit.hpp>
#include <cxbqn/types.hpp>

namespace cxbqn::types {

struct Scope : public std::enable_shared_from_this<Scope> {

  /* Create a new root scope */
  static O<Scope> root_scope(O<CompUnit> cu,
                             O<std::unordered_map<std::string, uz>> exported);

  /* Create a new child scope */
  static O<Scope> child_scope(W<Scope> parent, uz blk_idx);

  O<CompUnit> cu;

  /* Get a reference by traversing the scope lineage */
  O<Value> get(O<Reference> r);

  /* Set a reference by traversing the scope lineage */
  void set(bool should_var_be_set, O<Reference> r, O<Value> v);

  /* Get the parent scope `depth` generations up. */
  O<Scope> get_nth_parent(uz depth);

  /* When using references, we must have a way to traverse the scope lineage */
  W<Scope> parent;

  /*
   * Each scope contains some number of variables. For functions/modifiers,
   * the first six will always be the relevant members of 𝕤𝕩𝕨𝕣𝕗𝕘.
   */
  std::vector<O<Value>> vars;
  O<std::unordered_map<std::string, uz>> _exported = {};

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

  Scope(O<CompUnit> cu, uz bi, bool isroot)
      : cu{cu}, blk_idx{bi}, _root{isroot}, parent{O<Scope>{}} {}
  bool _root;
};

} // namespace cxbqn::types
