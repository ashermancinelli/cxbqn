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

}
