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
  stack.resize(cxbqn::config::init_stack_size());
  spdlog::debug("init stack size={}", stack.capacity());
  Env e;
  std::size_t prog_counter = 0;
  int ret = vm(e, code, prog_counter, stack);
  return ret;
}

}
