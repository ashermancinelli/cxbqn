#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <spdlog/spdlog.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

void usage() {
  //__DATE__
  fmt::print("\n");
}

int main(int argc, char **argv) {

  std::vector<std::string> args(argv, argv+argc);

  try {

    const auto provide = provides::get_provides()->values;
    CompileParams p(
#include <cxbqn/__/compiled_runtime_annot>
    );
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);

    auto rt = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

    auto setprims = runtime_ret->values[1];

    // Inform the two latter builtins of the runtime so they can refer to it
    auto decompose = make_shared<Decompose>(rt);
    auto primind = make_shared<PrimInd>(rt);

    setprims->call(1, {setprims, O<Array>(new Array({decompose, primind})), bi_Nothing()});

    auto runtime = rt->values;
    CompileParams p2(
#include <cxbqn/__/compiled_compiler_annot>
    );

    fmt::print("running compiler bc\n");
    auto cret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies,
                        p2.source_indices, p2.source_str);

    auto compiler = cret.v;

    fmt::print("calling compiler\n");
    auto bc = compiler->call(2, {compiler, O<Value>(new Array(U"5+5")), rt});
    fmt::print("compiler returned {}\n", CXBQN_STR_NC(bc));
  } catch (std::runtime_error &e) {
    fmt::print("{}\n", e.what());
    return 1;
  }

  fmt::print("done\n");
  return 0;
}
