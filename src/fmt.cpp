#include <fmt.hpp>
#include <spdlog/spdlog.h>

namespace cxbqn::fmt {

std::ostream &repr(std::ostream &os, Value *v) {
  Array *a;
  Number *n;
  Function *f;
  Reference *r;

  // using t() is faster than attempting to dynamic cast on every type
  switch (v->t()) {
  case t_Array:
    a = dynamic_cast<Array *>(v);
    os << "A{sh=";
    for (const auto &sh : a->shape)
      os << sh << ",";
    os << "}";
    break;
  case t_Number:
    n = dynamic_cast<Number *>(v);
    os << "N{" << n->v << "}";
    break;
  case t_Function:
    f = dynamic_cast<Function *>(v);
    os << "F{}";
    break;
  case t_Reference:
    r = dynamic_cast<Reference*>(v);
    os << "R{d="<< r->depth << ",pos="<<r->position_in_parent<<"}";
    break;
  default:
    spdlog::critical("got t()={}", v->t());
    throw std::runtime_error(
        "could not find type of value passed to fmt::repr");
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, Body b) {
  return os << "Body{bc=" << b.bc_offset << ",nvars=" << b.var_count << "}";
}

std::ostream &operator<<(std::ostream &os, Block b) {
  return os << "Block{ty=" << static_cast<int>(b.type)
            << ",imm=" << std::boolalpha << b.immediate
            << ",body=" << b.body_idx << "}";
}

} // namespace cxbqn::fmt
