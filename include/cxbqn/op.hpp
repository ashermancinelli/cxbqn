#pragma once

namespace cxbqn::op {

enum {
  PUSH = 0x00, // N; push object from objs[N]
  DFND = 0x01, // N; push dfns[N], derived to current scope
  SYSV = 0x02, // N; get system function N

  POPS = 0x06, // pop object from stack
  RETN = 0x07, // returns top of stack
  RETD = 0x08, // return a namespace of exported items
  ARRO = 0x0B, // N; create a vector of top N items
  ARRM = 0x0C, // N; create a mutable vector of top N items

  FN1C = 0x10, // monadic function call ⟨…,x,f  ⟩ → F x
  FN2C = 0x11, //  dyadic function call ⟨…,x,f,w⟩ → w F x
  FN1O = 0x12, // monadic call, checking for ·
  FN2O = 0x13, // dyadic call, checking for ·
  TR2D = 0x14, // derive 2-train aka atop; ⟨…,  g,f⟩ → (f g)
  TR3D = 0x15, // derive 3-train aka fork; ⟨…,h,g,f⟩ → (f g h)
  CHKV = 0x16, // throw error if top of stack is ·
  TR3O = 0x17, // TR3D but creates an atop if F is ·

  MD1C = 0x1A, // call/derive 1-modifier; ⟨…,  _m,f⟩ → (f _m)
  MD2C = 0x1B, // call/derive 2-modifier; ⟨…,g,_m,f⟩ → (f _m_ g)
  MD2L = 0x1C, // derive 2-modifier to 1-modifier with 𝔽 ⟨…,_m_,f⟩ → (f _m_)
  MD2R = 0x1D, // derive 2-modifier to 1-modifier with 𝔾 ⟨…,g,_m_⟩ → (_m_ g)

  VARO = 0x20, // N0,N1; push variable at depth N0 and position N1
  VARM = 0x21, // N0,N1; push mutable variable at depth N0 and position N1
  VARU = 0x22, // N0,N1; like VARO but overrides the slot with bi_optOut
  DYNO = 0x26, // N; push variable with name objs[N]
  DYNM = 0x27, // N; push mutable variable with name objs[N]

  PRED = 0x2A, // pop item, go to next body if 0, continue if 1
  VFYM = 0x2B, // push a mutable version of ToS that fails if set to a non-equal
               // value (for header assignment)
  NOTM = 0x2C, // push null reference that always matches
  SETH = 0x2F, // set header; acts like SETN, but it doesn't push to stack,
               // and, instead of erroring in cases it would, it skips to the
               // next body
  SETN = 0x30, // set new; _  ←_; ⟨…,x,  mut⟩ → mut←x
  SETU = 0x31, // set upd; _  ↩_; ⟨…,x,  mut⟩ → mut↩x
  SETM = 0x32, // set mod; _ F↩_; ⟨…,x,F,mut⟩ → mut F↩x
  SETC = 0x33, // set call; _ F↩; (…,  F,mut) → mut F↩
  FLDO = 0x40, // N; get field nameList[N] from ToS
  FLDM = 0x41, // N; get mutable field nameList[N] from ToS
  ALIM = 0x42, // N; replace ToS with one with a namespace field alias N
  BC_SIZE
};

// Lengths of each bytecode+arguments
u8 bc_len(u8);

} // namespace cxbqn::op
