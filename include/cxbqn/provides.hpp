#pragma once
#include <cxbqn/cxbqn.hpp>

namespace cxbqn::provides {

using namespace cxbqn::types;

struct Type : public Function {
  virtual TypeType t() const {
    return TypeType{t_Function | annot(t_Primitive)};
  }
  std::ostream &repr(std::ostream &os) const override { return os << "•Type"; }
  Value *call(u8 nargs = 0, std::vector<Value *> args = {}) override;
};

} // namespace cxbqn::provides
