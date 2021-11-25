#include "driver.hpp"

#ifdef CXBQN_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#endif

namespace cxbqn::driver {

static std::vector<std::string> curr_names = {};

#ifdef CXBQN_READLINE
char *match_names(const char *text, int state) {
  static uz len, i;

  if (!state) {
    len = strlen(text);
    i = 0;
  }

  while (i < curr_names.size()) {
    if (curr_names[i++].starts_with(text))
      return strdup(curr_names[i - 1].c_str());
  }

  return nullptr;
}

char **scp_name_completion(const char *text, int start, int end) {
  rl_attempted_completion_over = 1;
  return rl_completion_matches(text, match_names);
}
#endif

bool getline(std::string &line) {
#ifdef CXBQN_READLINE
  auto *buf = readline("   ");
  if (nullptr == buf)
    return false;
  if (strlen(buf) > 0) {
    add_history(buf);
  }
  line.resize(strlen(buf));
  std::copy(buf, buf + strlen(buf), line.begin());
  free(buf);
  return true;
#else
  fmt::print("   ");
  return (bool)std::getline(std::cin, line);
#endif
}

static inline O<Array> to_arr(std::vector<std::string> n) {
  auto ar = make_shared<Array>(n.size());
  for (int i = 0; i < n.size(); i++)
    ar->values[i] = make_shared<Array>(n[i]);
  return ar;
}

int repl(O<Value> compiler, O<Array> bqnruntime, O<Value> sysfn_handler,
         O<Value> fmt) {

#ifdef CXBQN_READLINE
  rl_attempted_completion_function = &scp_name_completion;
#endif

  std::string line;
  if (!getline(line))
    return 1;

  auto compw = make_shared<Array>(4);
  compw->values[0] = bqnruntime;
  compw->values[1] = sysfn_handler;
  compw->values[2] = make_shared<Array>(0);   // no names currently in scope
  compw->values[3] = make_shared<Number>(-1); // allow shadowing

  auto src = make_shared<Array>(line);
  auto compiled = compiler->call(2, {compiler, src, compw});
  auto runret = vm::run(compiled);

  {
    auto formatted = fmt->call(1, {fmt, runret.v, bi_Nothing()});
    fmt::print("{}\n", dyncast<Array>(formatted)->to_string());
  }

  // Now that we've gotten the repl started with the first execution, we pass
  // the existing names back into the compiler so all the variables exist in the
  // global scope.
  auto scp = runret.scp;
  compw->values[2] = to_arr(scp->names);
  curr_names = scp->names;

  while (getline(line)) {

    if (0 == line.size())
      continue;

    auto src = make_shared<Array>(line);
    compw->values[2] = to_arr(scp->names);
    auto compiled = compiler->call(2, {compiler, src, compw});
    auto cu = vm::deconstruct(compiled);

    auto body = cu->_bodies[cu->_blocks[0].body_idx(0)];

    // extend slots to hold new variables
    scp->vars.resize(body.var_count + scp->vars.size());

    // Extend names with names from new compilation unit
    curr_names = scp->names = cu->_namelist;
    auto ret = vm::vm(cu, scp, body);

    // By default, print the result
    auto formatted = fmt->call(1, {fmt, ret, bi_Nothing()});
    fmt::print("{}\n", dyncast<Array>(formatted)->to_string());
  }

  return 0;
}

int version() {
  fmt::print("CXBQN {}\ncompiled on " __DATE__ "\n", cxbqn::config::version());
  return 1;
}

int usage() {
  version();
  fmt::print("usage: BQN [options] [arguments]\n");
  fmt::print("\t-e <string>: execute BQN expression\n");
  fmt::print(
      "\t-p <string>: execute BQN expression, pretty print the result\n");
  fmt::print("\t-f <file>: execute <file>\n");
  fmt::print("\t-r: start repl (WIP)\n");
  fmt::print("\t-h, --help: print this message\n");
  fmt::print("\t-v, --version: show full version information\n");
  fmt::print("\t-x: show compilation unit before executing\n");
  return 1;
}

int parse_args(std::vector<std::string> args, O<Array> &path, O<Array> &src,
               O<Array> sysargs, bool &repl, bool &pp_res, bool &show_cu) {
  auto it = args.begin();
  it++; // skip exe name

  while (it != args.end()) {
    if ("-e" == *it) {
      repl = false;
      it++;
      auto _src = *it;
      src.reset(new Array(_src));
    } else if ("-p" == *it) {
      pp_res = true;
      it++;
    } else if ("-x" == *it) {
      show_cu = true;
      it++;
    } else if ("-v" == *it or "--version" == *it) {
      return version();
    } else if ("-h" == *it or "--help" == *it) {
      return usage();
    } else if ("-r" == *it) {
      repl = true;
      it++;
    } else if ("-f" == *it) {
      repl = false;
      it++;
      auto f = fs::path(*it);
      if (!fs::exists(f)) {
        fmt::print("path {} does not exist\n", f);
        return 1;
      }
      path.reset(new Array(fs::absolute(f)));
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
    } else {
      for (; it != args.end(); it++) {
        sysargs->values.push_back(O<Value>(new Array(*it)));
        sysargs->shape[0]++;
      }
      return 0;
    }
  }

  return 0;
}

} // namespace cxbqn::driver
