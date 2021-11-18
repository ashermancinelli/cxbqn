#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <spdlog/spdlog.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

int main(int argc, char **argv) {
  auto rt = provides::get_runtime_setprims_annot();

  auto runtime = rt->values;
  CompileParams p(
#include <cxbqn/__/compiled_compiler>
  );

  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

  auto compiler = ret.v;

  auto source = O<Array>(new Array(U"5+5"));
  std::vector<O<Value>>
      cargs; //{compiler, make_shared<Array>(U"5+5"), runtime};
  cargs.push_back(compiler);
  cargs.push_back(source);
  cargs.push_back(rt);
  // auto bc = compiler->call(2, {compiler, O<Value>(new Array(U"5+5")), rt});
  auto bc = compiler->call(2, cargs);

  fmt::print("done\n");
  return 0;
}
