#include "driver.hpp"

namespace cxbqn::driver {

int repl(O<Value> compiler, O<Array> bqnruntime, O<Value> sysfn_handler,
         O<Value> fmt) {
  fmt::print("   ");
  for (std::string line; std::getline(std::cin, line); fmt::print("   ")) {

    if (0 == line.size())
      continue;

    auto compw = make_shared<Array>(2);
    compw->values[0] = bqnruntime;
    compw->values[1] = sysfn_handler;
    //compw->values[2] = bi_Nothing();
    //compw->values[3] = bi_Nothing();

    auto src = make_shared<Array>(line);
    auto compiled = compiler->call(2, {compiler, src, compw});
    auto runret = vm::run(compiled);

    // By default, print the result
    auto formatted = fmt->call(1, {fmt, runret.v, bi_Nothing()});
    fmt::print("{}\n", dynamic_pointer_cast<Array>(formatted)->to_string());
  }

  return 0;
}

int version() {
  fmt::print("CXBQN {}\ncompiled on " __DATE__ "\n", cxbqn::config::version());
  return 1;
}

int usage() {
  version();
  fmt::print("usage: BQN [options] [file.bqn [arguments]]\n");
  fmt::print("\t-e <string>: execute BQN expression\n");
  fmt::print("\t-f <file>: execute <file>\n");
  fmt::print("\t-i: start repl (WIP)\n");
  fmt::print("\t-h, --help: print this message\n");
  fmt::print("\t-v, --version: show full version information\n");
  return 1;
}

int parse_args(std::vector<std::string> args, O<Array> &src, O<Array> sysargs,
               bool &repl) {
  auto it = args.begin();
  it++; // skip exe name

  while (it != args.end()) {
    if ("-e" == *it) {
      repl = false;
      it++;
      auto _src = *it;
      src.reset(new Array(_src));
      continue;
    }
    if ("-v" == *it or "--version" == *it) {
      return version();
    }
    if ("-h" == *it or "--help" == *it) {
      return usage();
    }
    if ("-i" == *it) {
      repl = true;
    }
    if ("-f" == *it) {
      repl = false;
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
        src.reset(new Array(_src));
        sysargs->values.push_back(O<Value>(new Array(std::string(f))));
        sysargs->shape[0]++;
        continue;
      } else {
        fmt::print("could not open path {}\n", f);
        return 1;
      }
    }
    sysargs->values.push_back(O<Value>(new Array(*it)));
    sysargs->shape[0]++;
    it++;
  }

  return 0;
}

} // namespace cxbqn::driver
