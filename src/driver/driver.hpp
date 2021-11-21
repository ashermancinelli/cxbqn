#pragma once
#include <chrono>
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <utf8.h>
namespace fs = std::filesystem;

namespace cxbqn::driver {

int version();
int usage();
int parse_args(std::vector<std::string> args, O<Array> &src, O<Array> sysargs, bool& repl);

} // namespace cxbqn::driver
