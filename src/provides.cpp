#include <provides.hpp>
#include <spdlog/spdlog.h>

namespace cxbqn::provides {

Value *Type::operator()(Value *x) {
  spdlog::debug("•Type(x)");
  using namespace cxbqn::types;
#define RET_TV(T, v)                                                           \
  if (nullptr != dynamic_cast<T *>(x))                                         \
    return new Number(v);
  RET_TV(Array, 0);
  RET_TV(Number, 1);
  RET_TV(Character, 2);
  RET_TV(Md1, 4);
  RET_TV(UserMd1, 4);
  RET_TV(Md2, 5);
  RET_TV(UserMd2, 5);
  RET_TV(UserFn, 3);
  RET_TV(Function, 3);
#undef RET_TV
  throw std::runtime_error("value type could not be found");
}

Value *Type::operator()(Value *, Value *) {
  throw std::runtime_error("no dyadic •Type");
}

} // namespace cxbqn::provides
