#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <utf8.h>
#include <chrono>
namespace fs = std::filesystem;

using namespace std::chrono;
using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::sys;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

std::size_t replace_all(std::string &inout, std::string_view what,
                        std::string_view with) {
  std::size_t count{};
  for (std::string::size_type pos{};
       inout.npos != (pos = inout.find(what.data(), pos, what.length()));
       pos += with.length(), ++count) {
    inout.replace(pos, what.length(), with.data(), with.length());
  }
  return count;
}

void version() {
  fmt::print("CXBQN {}: compiled on " __DATE__ "\n", cxbqn::config::version());
}

int usage() {
  version();
  fmt::print("usage: BQN [options] [file.bqn [arguments]]\n");
  fmt::print("\t-e <string>: execute BQN expression\n");
  fmt::print("\t-f <file>: execute <file>\n");
  return 1;
}

static O<Value> src;

int parse_args(std::vector<std::string> args) {
  auto it = args.begin();
  it++; // skip exe name

  while (it != args.end()) {
    if ("-e" == *it) {
      it++;
      auto _src = *it;
      src.reset(new Array(_src));
      return 0;
    }
    if ("-h" == *it or "--help" == *it) {
      return usage();
    }
    if ("-f" == *it) {
      it++;
      auto f = fs::path(*it);
      if (!fs::exists(f)) {
        fmt::print("path {} does not exist\n", f);
        return 1;
      }
      std::string _src = "";
      if (std::FILE *fp = std::fopen(f.c_str(), "r")) {
        int ch;
        while ((ch = fgetc(fp)) != EOF) {
          _src += ch;
        }
        std::fclose(fp);
        fmt::print("{}\n", _src);
        src.reset(new Array(_src));
        return 0;
      } else {
        fmt::print("could not open path {}\n", f);
        return 1;
      }
      return usage();
    }
  }

  return 0;
}

int main(int argc, char **argv) {

  std::vector<std::string> args(argv, argv + argc);
  if (auto ec = parse_args(args))
    return ec;

  try {

    auto t_start = std::chrono::high_resolution_clock::now();
    const auto provide = provides::get_provides()->values;
    CompileParams p(
#include <cxbqn/__/compiled_runtime>
    );
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);

#ifdef CXBQN_PROFILE_STARTUP
    auto t_rt = std::chrono::high_resolution_clock::now();
#endif

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

    auto cret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies);
#ifdef CXBQN_PROFILE_STARTUP
    auto t_comp = std::chrono::high_resolution_clock::now();
#endif

    auto compiler = cret.v;

    // Evaluating the formatter bytecode returns [fmt1, repr]. We then use fmt1
    // to create the actual formatter by passing it four arguments, •Type,
    // •Decompose, •Glyph, and •FmtNum.
    CompileParams pfmt(
#include <cxbqn/__/compiled_formatter>
    );
    auto fmtret = vm::run(pfmt.bc, pfmt.consts.v, pfmt.blk_defs, pfmt.bodies);
#ifdef CXBQN_PROFILE_STARTUP
    auto t_fmt = std::chrono::high_resolution_clock::now();
#endif
    auto fmt1 = fmtret.v;

    auto glyph = make_shared<Glyph>(bqnruntime);
    auto fmtnum = make_shared<FmtNum>();
    auto _fmtarr = fmt1->call(
        1, {fmt1, O<Value>(new Array({bi_Type(), decompose, glyph, fmtnum})),
            bi_Nothing()});

    auto fmtarr = dynamic_pointer_cast<Array>(_fmtarr);
    auto fmt = fmtarr->values[0];

    // Here, we could just call the compiler with the runtime as 𝕨. To add the
    // system functions, we will pass another value in an array along with the
    // runtime. This funcionality is not documented at the time of writing.
    auto compw = make_shared<Array>(2);
    compw->values[0] = bqnruntime;
    compw->values[1] = bi_SystemFunctionResolver();
    auto compiled = compiler->call(2, {compiler, src, compw});

    auto runret = vm::run(compiled);
    auto formatted = fmt->call(1, {fmt, runret.v, bi_Nothing()});

    fmt::print("{}\n", dynamic_pointer_cast<Array>(formatted)->to_string());

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
