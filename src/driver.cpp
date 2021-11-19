#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <utf8.h>
namespace fs = std::filesystem;

using namespace cxbqn;
using namespace cxbqn::types;
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
          if (ch == '\n')
            utf8::append(U'⋄', _src);
          else
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

    const auto provide = provides::get_provides()->values;
    CompileParams p(
#include <cxbqn/__/compiled_runtime>
    );
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);

    auto rt = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

    auto setprims = runtime_ret->values[1];

    // Inform the two latter builtins of the runtime so they can refer to it
    auto decompose = make_shared<Decompose>(rt);
    auto primind = make_shared<PrimInd>(rt);

    setprims->call(
        1, {setprims, O<Array>(new Array({decompose, primind})), bi_Nothing()});

    auto runtime = rt->values;
    CompileParams p2(
#include <cxbqn/__/compiled_compiler>
    );

    auto cret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies);

    auto compiler = cret.v;

    CompileParams pfmt(
#include <cxbqn/__/compiled_formatter>
    );
    auto fmtret = vm::run(pfmt.bc, pfmt.consts.v, pfmt.blk_defs, pfmt.bodies);
    auto fmt1 = fmtret.v;

    auto glyph = make_shared<Glyph>(rt);
    auto fmtnum = make_shared<FmtNum>();
    auto fmt = fmt1->call(
        1, {fmt1, O<Value>(new Array({bi_Type(), decompose, glyph, fmtnum})),
            bi_Nothing()});

    auto compiled = compiler->call(2, {compiler, src, rt});

    auto runret = vm::run(compiled);
    // auto formatted = fmt->call(1, {fmt, runret.v, bi_Nothing()});
    fmt::print("{}\n", *runret.v);
    // fmt::print("formatted: {}\n", *formatted);
  } catch (std::runtime_error &e) {
    fmt::print("{}\n", e.what());
    return 1;
  }
  return 0;
}
