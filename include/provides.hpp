#pragma once
#include <cxbqn.hpp>

namespace cxbqn::provides {

using cxbqn::types::Value;

struct Type : types::Builtin {
  Value* operator()(Value*x) override;
  Value* operator()(Value*,Value*) override;
};

struct Plus : types::Builtin {
  Value* operator()(Value*x) override;
  Value* operator()(Value*,Value*) override;
};

struct Fill : types::Builtin {};

}
