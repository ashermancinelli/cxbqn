#pragma once
#include <cxbqn/types.hpp>

namespace cxbqn::types {

struct Scope : public std::enable_shared_from_this<Scope> {

  /* Create a new root scope */
  static O<Scope> root_scope(std::vector<Block> blks, ByteCode bc,
                             std::vector<O<Value>> consts,
                             std::vector<Body> bods);

  /* Create a new child scope */
  static O<Scope> child_scope(W<Scope> parent, uz blk_idx);

  /*
   * Get a span of the bytecode owned by a scope somewhere up the scope lineage,
   * potentially owned by this scope.
   */
  const ByteCodeRef bc() const;

  std::vector<O<Value>> consts() const;

  std::span<const Block> blocks() const;

  std::span<const Body> bodies() const;

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

  /*
   * Possibly own the consts passed to the top-level `vm::run` call if this is
   * a root scope. Otherwise, `Scope::consts` will retrieve the consts from
   * somewhere up the scope lineage.
   */
  std::optional<std::vector<O<Value>>> _consts;

  /*
   * Blocks and bodies use non-owning/reference semantics when passing around
   * bytecode, and Scope is the owner of the bytecode.
   *
   * \see Block::body()
   * \see Scope::bc()
   */
  std::optional<ByteCode> _bc;

  std::optional<std::vector<Block>> _blks;

  std::optional<std::vector<Body>> _bods;

  const uz blk_idx;

  Scope(uz bi) : blk_idx{bi}, parent{O<Scope>{}} {}
};

}
