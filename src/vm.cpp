#include <cxbqn.hpp>
#include <spdlog/spdlog.h>

namespace cxbqn::vm {

int vm(Env &e, Code& code, std::size_t &prog_counter, std::vector<int>& stack) {
  spdlog::set_pattern("vm::execute[%^%l%$]:%v");
  return 0;
}

int run(Code &code, Objects &objs, Sections &sections) {
  spdlog::set_pattern("vm::run[%^%l%$]:%v");
  std::vector<int> stack;
  stack.reserve(cxbqn::config::init_stack_size());
  spdlog::debug("init stack size={}", stack.capacity());
  Env e;
  std::size_t prog_counter = 0;
  vm(e, code, objs, prog_counter, stack);
  return 0;
}

}
