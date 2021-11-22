#pragma once
#include <chrono>
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <cxbqn/fs.hpp>
#include <spdlog/spdlog.h>
#include <utf8.h>

namespace cxbqn::driver {

int version();
int usage();
int parse_args(std::vector<std::string> args, O<Array> &src, O<Array> sysargs,
               bool &repl, bool& pp_res);
int repl(O<Value> compiler, O<Array> bqnruntime, O<Value> sysfn_handler,
         O<Value> fmt);

} // namespace cxbqn::driver
