#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

void arro(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  const auto list_len = bc[++pc];
  auto *ar = new Array(list_len, stk);
  stk.push_back(ar);
}

void arrm(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  const auto list_len = bc[++pc];
  auto *ar = new RefArray(list_len, stk);
  stk.push_back(ar);
}

void md1c(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp) {
  auto *f = stk.back();
  stk.pop_back();

  auto *opaque_r = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md1c:r={},f={}", CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(f));

  auto *r = dynamic_cast<BlockInst *>(opaque_r);
  if (r->imm()) {
    auto *v = r->call(1, {nullptr, nullptr, nullptr, opaque_r, f, nullptr});
    stk.push_back(v);
  } else {
    r->deferred_args.assign({nullptr, nullptr, nullptr, opaque_r, f, nullptr});
    stk.push_back(opaque_r);
  }
}

void md2c(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp) {
  auto *f = stk.back();
  stk.pop_back();

  auto *opaque_r = stk.back();
  stk.pop_back();

  auto *g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md1c:(F _r_ G)=({} {} {})", CXBQN_STR_NC(f),
              CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(g));

  auto *r = dynamic_cast<BlockInst *>(opaque_r);

  if (r->imm()) {
    auto *v = r->call(2, {nullptr, nullptr, nullptr, opaque_r, f, g});
    stk.push_back(v);
  } else {
    r->deferred_args.assign({nullptr, nullptr, nullptr, opaque_r, f, g});
    stk.push_back(opaque_r);
  }
}

void tr2d(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp) {
  auto* f = stk.back();
  stk.pop_back();

  auto* g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr2d:f={},g={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g));

  stk.push_back(new Atop(f, g));
}

} // namespace cxbqn::vm::instructions
