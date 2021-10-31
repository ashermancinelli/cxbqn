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

void md1c(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  auto *f = stk.back();
  stk.pop_back();

  auto *modif = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("MD1C:modif={},f={}", CXBQN_STR_NC(modif), CXBQN_STR_NC(f));

  auto *ret = modif->call({modif, f});

  CXBQN_DEBUG("MD1C:ret={}", CXBQN_STR_NC(ret));
  stk.push_back(ret);
}

} // namespace cxbqn::vm::instructions
