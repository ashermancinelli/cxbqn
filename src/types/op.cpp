#include <cxbqn/cxbqn.hpp>

namespace cxbqn::op {

u8 bc_len(u8 op) {
  static cxbqn::u8 bc_lens[BC_SIZE];
  bc_lens[NOTM] = 0;
  bc_lens[FN1C] = 1;
  bc_lens[FN2C] = 1;
  bc_lens[MD1C] = 1;
  bc_lens[MD2C] = 1;
  bc_lens[MD2R] = 1;
  bc_lens[TR2D] = 1;
  bc_lens[TR3D] = 1;
  bc_lens[TR3O] = 1;
  bc_lens[SETN] = 1;
  bc_lens[SETU] = 1;
  bc_lens[SETM] = 1;
  bc_lens[SETH] = 1;
  bc_lens[SETC] = 1;
  bc_lens[POPS] = 1;
  bc_lens[CHKV] = 1;
  bc_lens[VFYM] = 1;
  bc_lens[RETN] = 1;
  bc_lens[RETD] = 1;
  bc_lens[PRED] = 1;
  bc_lens[PUSH] = 2;
  bc_lens[DFND] = 2;
  bc_lens[ARRO] = 2;
  bc_lens[ARRM] = 2;
  bc_lens[DYNO] = 2;
  bc_lens[DYNM] = 2;
  bc_lens[FLDO] = 2;
  bc_lens[FLDM] = 2;
  bc_lens[SYSV] = 2;
  bc_lens[ALIM] = 2;
  bc_lens[VARO] = 3;
  bc_lens[VARM] = 3;
  bc_lens[VARU] = 3;
  return bc_lens[op];
}

} // namespace cxbqn::op
