#include <cxbqn.hpp>
#include <spdlog/spdlog.h>

int main() {
  using namespace cxbqn;
  using namespace cxbqn::vm;
  int fail{0};
  spdlog::set_level(spdlog::level::debug);
  Bytecode bc;
  Objects objs;
  Sections scs;
  fail = run(bc, objs, scs);
  return fail;
}
