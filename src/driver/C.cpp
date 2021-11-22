#include "driver.hpp"
#include <fstream>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::sys;

void usage() {
  fmt::print("C: compile BQN expressions using CXBQN.\n");
  fmt::print("-c <string>: compile BQN expression\n");
  fmt::print("-f <file>: compile contents of file\n");
}

int main(int argc, char **argv) {

  bool repl, pp_res;
  std::vector<std::string> args(argv, argv + argc);
  auto it = args.begin();
  it++;

  O<Value> src;
  auto path = make_shared<Array>(0);
  if ("-c" == *it) {
    it++;
    src.reset(new Array(*it));
  } else if ("-f" == *it) {
    std::string _src = "";
    it++;
    std::ifstream f{(*it).c_str()};
    for (std::string line; std::getline(f, line);) {
      _src += "\n" + line;
    }
    src.reset(new Array(_src));
  } else {
    fmt::print("Invalid option {}.\n", *it);
    usage();
    return 1;
  }

  try {

    auto t_start = std::chrono::high_resolution_clock::now();
    const auto provide = provides::get_provides()->values;
    CompileParams p(
#include <cxbqn/__/compiled_runtime>
    );
    auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
    auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);

    auto bqnruntime = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

    auto setprims = runtime_ret->values[1];

    // Inform the two latter builtins of the runtime so they can refer to it
    auto decompose = make_shared<Decompose>(bqnruntime);
    auto primind = make_shared<PrimInd>(bqnruntime);

    setprims->call(
        1, {setprims, O<Array>(new Array({decompose, primind})), bi_Nothing()});

    auto runtime = bqnruntime->values;
    CompileParams p2(
#include <cxbqn/__/compiled_compiler>
    );

    auto cret = vm::run(p2.bc, p2.consts.to_arr(), p2.blk_defs, p2.bodies);

    auto compiler = cret.v;

    // Evaluating the formatter bytecode returns [fmt1, repr]. We then use fmt1
    // to create the actual formatter by passing it four arguments, •Type,
    // •Decompose, •Glyph, and •FmtNum.
    CompileParams pfmt(
#include <cxbqn/__/compiled_formatter>
    );
    auto fmtret =
        vm::run(pfmt.bc, pfmt.consts.to_arr(), pfmt.blk_defs, pfmt.bodies);
    auto fmt1 = fmtret.v;

    auto glyph = make_shared<Glyph>(bqnruntime);
    auto fmtnum = make_shared<FmtNum>();
    auto _fmtarr = fmt1->call(
        1, {fmt1, O<Value>(new Array({bi_Type(), decompose, glyph, fmtnum})),
            bi_Nothing()});

    auto fmtarr = dynamic_pointer_cast<Array>(_fmtarr);
    auto fmt = fmtarr->values[0];
    auto repr = fmtarr->values[1];
    auto dofmt = [fmt](auto v) {
      auto formatted = fmt->call(1, {fmt, v, bi_Nothing()});
      fmt::print("{}\n", dynamic_pointer_cast<Array>(formatted)->to_string());
    };

    // Here, we could just call the compiler with the runtime as 𝕨. To add the
    // system functions, we will pass another value in an array along with the
    // runtime. This funcionality is not documented at the time of writing.
    auto compw = make_shared<Array>(2);
    compw->values[0] = bqnruntime;

    // It may seem counterintuitive to pass the compiler and compiler arguments
    // to the sys func resolver which is itself part of the compiler arguments,
    // but this is needed for •Import to work without recreating the compiler
    compw->values[1] = O<Value>(new SystemFunctionResolver(
        make_shared<Array>(0), fmt, repr, compiler, bqnruntime, path));

    auto compiled = compiler->call(2, {compiler, src, compw});

    auto c = dynamic_pointer_cast<Array>(compiled);
    for (int i = 0; i < c->N(); i++)
      dofmt(c->values[i]);

  } catch (std::runtime_error &e) {
    fmt::print("{}\n", e.what());
    return 1;
  }
  return 0;
}
