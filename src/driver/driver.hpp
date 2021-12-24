#pragma once
#include <chrono>
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <cxbqn/fs.hpp>
#include <cxbqn/rt_native.hpp>
#include <spdlog/spdlog.h>
#include <utf8.h>

namespace cxbqn::driver {

#ifdef CXBQN_MEM_shared_ptr
#define CXBQN_PTR_RESET(ptr, newptr) ptr.reset(newptr);
#elif CXBQN_MEM_leak
#define CXBQN_PTR_RESET(ptr, newptr) ptr = newptr;
#else
#error "unsupported"
#endif

int version();
int usage();
int parse_args(int argc, char** argv, O<Array> &path, O<Array> &src,
               O<Array> sysargs, bool &repl, bool &pp_res, bool& show_cu);
int repl(O<Value> compiler, O<Array> bqnruntime, O<Value> sysfn_handler,
         O<Value> fmt, bool show_cu);

} // namespace cxbqn::driver
