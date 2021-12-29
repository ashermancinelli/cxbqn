#include "driver.hpp"

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::sys;

int main(int argc, char **argv) {

  bool repl = false, pp_res = false, show_cu = false;
  auto sysargs = CXBQN_NEW(Array, 0);
  auto path = CXBQN_NEW(Array, 0);
  auto src = CXBQN_NEW(Array, "\"CXBQN internal: Empty program\" ! 0");

  std::vector<std::string> args(argv, argv + argc);

  if (auto ec = driver::parse_args(argc, argv, path, src, sysargs, repl, pp_res,
                                   show_cu))
    return ec;

  try {

#ifdef CXBQN_PROFILE_STARTUP
    auto t_start = std::chrono::high_resolution_clock::now();
#endif

    const auto provide = provides::get_provides()->values;
    auto rt0_cu =
#include <cxbqn/__/r0>
        ;
    auto ret0 = dyncast<Array>(vm::run(rt0_cu).v);

    rt_native::replace_r0_with_native(ret0);

    auto runtime_0 = ret0->values;

    auto rt1_cu =
#include <cxbqn/__/r1>
        ;
    auto ret1 = vm::run(rt1_cu);
    auto runtime_ret = dyncast<Array>(ret1.v);

#ifdef CXBQN_PROFILE_STARTUP
    auto t_rt = std::chrono::high_resolution_clock::now();
#endif

    auto bqnruntime = dyncast<Array>(runtime_ret->values[0]);

    rt_native::replace_r1_with_native(bqnruntime);

    auto setprims = runtime_ret->values[1];

    // Inform the two latter builtins of the runtime so they can refer to it
    auto decompose = CXBQN_NEW(Decompose, bqnruntime);
    auto primind = CXBQN_NEW(PrimInd, bqnruntime);

    {
      Args a{setprims, O<Array>(new Array({decompose, primind})), bi_Nothing()};
      setprims->call(1, a);
    }

    auto runtime = bqnruntime->values;
    auto c_cu =
#include <cxbqn/__/c>
        ;

    auto cret = vm::run(c_cu);
#ifdef CXBQN_PROFILE_STARTUP
    auto t_comp = std::chrono::high_resolution_clock::now();
#endif

    auto compiler = cret.v;

    // Evaluating the formatter bytecode returns [fmt1, repr]. We then use fmt1
    // to create the actual formatter by passing it four arguments, •Type,
    // •Decompose, •Glyph, and •FmtNum.
    auto f_cu =
#include <cxbqn/__/f>
        ;
    auto fmtret = vm::run(f_cu);
#ifdef CXBQN_PROFILE_STARTUP
    auto t_fmt = std::chrono::high_resolution_clock::now();
#endif
    auto fmt1 = fmtret.v;

    auto glyph = CXBQN_NEW(Glyph, bqnruntime);
    auto fmtnum = CXBQN_NEW(FmtNum);
    O<Value> _fmtarr;
    {
      auto x = CXBQN_NEW(Array, 4);
      x->values.assign({bi_Type(), decompose, glyph, fmtnum});
      Args a{fmt1, x, bi_Nothing()};
      _fmtarr = fmt1->call(1, a);
    }

    auto fmtarr = dyncast<ArrayBase>(_fmtarr);
    auto fmt = values(fmtarr)[0];
    auto repr = values(fmtarr)[1];

    // Here, we could just call the compiler with the runtime as 𝕨. To add the
    // system functions, we will pass another value in an array along with the
    // runtime. This funcionality is not documented at the time of writing.
    auto compw = CXBQN_NEW(Array, 2);
    compw->values[0] = bqnruntime;

    // It may seem counterintuitive to pass the compiler and compiler arguments
    // to the sys func resolver which is itself part of the compiler arguments,
    // but this is needed for •Import to work without recreating the compiler
    compw->values[1] = O<Value>(new SystemFunctionResolver(
        sysargs, fmt, repr, compiler, bqnruntime, path));

    if (repl) {
      return driver::repl(compiler, bqnruntime, compw->values[1], fmt, show_cu);
    } else {
      O<Value> compiled;
      {
        Args a{compiler, src, compw};
        compiled = compiler->call(2, a);
      }
      if (show_cu)
        for (auto v : values(dyncast<ArrayBase>(compiled)))
          fmt::print("{}\n", *v);
      auto runret = vm::run(compiled);
      if (pp_res) {
        Args a{fmt, runret.v, bi_Nothing()};
        auto formatted = fmt->call(1, a);
        fmt::print("{}\n", to_string(formatted));
      }
    }

#ifdef CXBQN_PROFILE_STARTUP
    auto t_final = std::chrono::high_resolution_clock::now();
    fmt::print("runtime: {}ms\ncompiler: {}ms\nexecute: {}ms\n",
               duration_cast<milliseconds>(t_rt - t_start).count(),
               duration_cast<milliseconds>(t_comp - t_start).count(),
               duration_cast<milliseconds>(t_final - t_start).count());
#endif

  } catch (std::runtime_error &e) {
    fmt::print("{}\n", e.what());
    return 1;
  }
  return 0;
}
