#include "driver.hpp"
#include <argparse.hpp>

#ifdef CXBQN_READLINE
namespace rl {
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
} // namespace rl
#endif

namespace cxbqn::driver {

static std::vector<std::string> curr_names = {"q", "quit"};

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
  rl::rl_attempted_completion_over = 1;
  return rl::rl_completion_matches(text, match_names);
}
#endif

bool getline(std::string &line) {
#ifdef CXBQN_READLINE
  auto *buf = rl::readline("   ");
  if (nullptr == buf)
    return false;
  if (strlen(buf) > 0) {
    rl::add_history(buf);
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

static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

static inline void chomp(std::string &s) {
  ltrim(s);
  rtrim(s);
}

static inline O<Array> to_arr(std::vector<std::string> n) {
  auto ar = CXBQN_NEW(Array, n.size());
  for (int i = 0; i < n.size(); i++)
    ar->values[i] = CXBQN_NEW(Array, n[i]);
  return ar;
}

int repl(O<Value> compiler, O<Array> bqnruntime, O<Value> sysfn_handler,
         O<Value> fmt, bool show_cu) {

#ifdef CXBQN_READLINE
  rl::rl_attempted_completion_function = &scp_name_completion;
#endif

  std::string line;
tryagain:
  if (!getline(line))
    return 1;
  chomp(line);
  if (!line.size())
    goto tryagain;
  if ("q" == line or "quit" == line)
    std::exit(0);

  auto compw = CXBQN_NEW(Array, 4);
  compw->values[0] = bqnruntime;
  compw->values[1] = sysfn_handler;
  compw->values[2] = CXBQN_NEW(Array, 0);   // no names currently in scope
  compw->values[3] = CXBQN_NEW(Number, -1); // allow shadowing

  auto src = CXBQN_NEW(Array, line);
  O<Value> compiled;
  {
    Args a{compiler, src, compw};
    compiled = compiler->call(2, a);
  }
  if (show_cu) {
    auto cu = dyncast<Array>(compiled);
    for (auto e : cu->values)
      fmt::print("{}\n", *e);
  }
  auto runret = vm::run(compiled);

  {
    Args a{fmt, runret.v, bi_Nothing()};
    auto formatted = fmt->call(1, a);
    fmt::print("{}\n", dyncast<Array>(formatted)->to_string());
  }

  // Now that we've gotten the repl started with the first execution, we pass
  // the existing names back into the compiler so all the variables exist in the
  // global scope.
  auto scp = runret.scp;
  compw->values[2] = to_arr(scp->names);
  curr_names = scp->names;

  while (getline(line)) {

    chomp(line);

    if (0 == line.size())
      continue;
    if ("q" == line or "quit" == line)
      std::exit(0);

    try {

      auto src = CXBQN_NEW(Array, line);
      compw->values[2] = to_arr(scp->names);
      O<Value> compiled;
      {
        Args a{compiler, src, compw};
        compiled = compiler->call(2, a);
      }
      if (show_cu) {
        auto cu = dyncast<Array>(compiled);
        for (auto e : cu->values)
          fmt::print("{}\n", *e);
      }
      auto cu = vm::deconstruct(compiled);

      auto body = cu->_bodies[cu->_blocks[0].body_idx(0)];

      // extend slots to hold new variables
      scp->vars.resize(body.var_count + scp->vars.size());

      // Extend names with names from new compilation unit
      curr_names = scp->names = cu->_namelist;
      auto ret = vm::vm(cu, scp, body);

      // By default, print the result
      {
        Args a{fmt, ret, bi_Nothing()};
        auto formatted = fmt->call(1, a);
        fmt::print("{}\n", dyncast<Array>(formatted)->to_string());
      }
    } catch (std::exception &e) {
      fmt::print("{}\n", e.what());
    }
  }

  return 0;
}

int parse_args(int argc, char **argv, O<Array> &path, O<Array> &src,
               O<Array> sysargs, bool &repl, bool &pp_res, bool &show_cu,
               std::optional<std::string> &comp_file) {

  // If no arguments are passed, just start up the repl
  repl = true;

  // the main program doesn't care if the source was passed by filename, so
  // we'll just keep track of this option here.
  auto file = false;

  argparse::ArgumentParser prog("BQN", config::version(),
                                argparse::default_arguments::help);

  // clang-format off
  prog.add_argument("-e", "--execute")
    .action([&] (const std::string& code) {
          repl = false;
          pp_res = false;
          CXBQN_PTR_RESET(src, new Array(code));
        })
    .help("execute a string as BQN code")
    .nargs(1);

  prog.add_argument("-v", "--version")
    .action([&] (const auto&) {
          fmt::print("CXBQN {} compiled on {}\n", config::version(), __DATE__);
          std::exit(0);
        })
    .help("prints version information and exits")
    .default_value(false)
    .implicit_value(true);

  prog.add_argument("-p", "--execute-and-print")
    .action([&] (const std::string& code) {
          repl = false;
          pp_res = true;
          CXBQN_PTR_RESET(src, new Array(code));
        })
    .help("execute a string as BQN code, pretty print the result")
    .nargs(1);

  prog.add_argument("-x", "--dump-cu")
    .action([&] (const auto&) { show_cu = true; })
    .help("dump compilation units after compiling")
    .default_value(false)
    .implicit_value(true);

  prog.add_argument("-r", "--repl")
    .action([&] (const auto&) { repl = true; })
    .help("enter REPL")
    .default_value(false)
    .implicit_value(true);

  prog.add_argument("-c", "--compile")
    .action([&] (const std::string& fname) {
          repl = false;
          comp_file = fname;
        })
    .help("[EXPERIMENTAL] compile BQN source file into executable")
    .nargs(1);

  prog.add_argument("-f", "--file")
    .action([&] (const std::string& fname) -> std::string {
          repl = false;
          auto f = fs::path(fname);
          if (!fs::exists(f)) {
            const auto s = fmt::format("path {} does not exist\n", f);
            throw std::runtime_error(s);
          }
          CXBQN_PTR_RESET(path, new Array(fs::absolute(f)));
          std::string _src = "";
          std::FILE *fp = std::fopen(f.c_str(), "r");
          if (!fp) {
            const auto s = fmt::format("could not open path {}\n", f);
            throw std::runtime_error(s);
          }
          int ch;
          while ((ch = fgetc(fp)) != EOF) {
            _src += ch;
          }
          std::fclose(fp);
          CXBQN_PTR_RESET(src, new Array(_src));
          sysargs->values.push_back(path);
          sysargs->shape[0]++;
          return fname;
        })
    .help("execute a BQN file")
    .nargs(1);

  prog.add_argument("args")
    .default_value(std::vector<std::string>())
    .help("all remaining arguments are passed into the BQN program as •args")
    .remaining();
  // clang-format on

  try {
    prog.parse_args(argc, argv);
  } catch (const std::exception &e) {
    fmt::print("{}\n{}", e.what(), prog);
  }

  const auto args = prog.get<std::vector<std::string>>("args");
  sysargs->shape[0] += args.size();
  for (const auto &a : args) {
    sysargs->values.push_back(CXBQN_NEW(Array, a));
  }

  return 0;
}

int full_compile(std::string_view fname, std::string_view out,
                 O<Value> compiler, O<Value> compw, O<Value> fmt) {
  //
}

} // namespace cxbqn::driver
