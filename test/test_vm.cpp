#include <cxbqn.hpp>
#include <spdlog/spdlog.h>

using namespace cxbqn;
using namespace cxbqn::vm;

int test_vm_5p5() {
  Code c;
  Sections scs;
  return run(c, scs);
}

int main() {
  int fail{0};
  spdlog::set_level(spdlog::level::debug);
  fail += test_vm_5p5();
  return fail;
}
