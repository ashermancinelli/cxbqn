#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void varo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          observer_ptr<Scope> scp) {
  const auto n_frames_up = bc[++pc];
  const auto local_variable_idx = bc[++pc];
  scp = scp->get_nth_parent(n_frames_up);
  CXBQN_DEBUG("varo:scope={},localidx={},framesup={}", *scp, local_variable_idx,
              n_frames_up);
  CXBQN_DEBUG_NC("varo:pushing var={}", scp->vars[local_variable_idx]);
  stk.push_back(scp->vars[local_variable_idx]);
}

} // namespace cxbqn::vm::instructions
