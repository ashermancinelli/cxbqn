#include <cstdint>
#include <memory>
#include <optional>
#include <spdlog/spdlog.h>
#include <value_types.hpp>

namespace cxbqn::value {

auto decode(Ref v) -> Scalar {
  spdlog::debug("value::decode Ref");
  if (v)
    return decode(*v);
  assert(false && "invalid shared ptr passed to value::decode");
}

auto decode(Opt v) -> Scalar {
  spdlog::debug("value::decode Opt");
  if (v.has_value())
    return decode(v.value());
  assert(false && "nullopt passed to value::decode");
}

auto decode(Root v) -> Scalar {
  spdlog::debug("value::decode Root");
  Scalar ret;
  std::visit(overload{
                 [&](Scalar vv) { ret = vv; },
                 [](BlockInst) { assert(false && "unsupported"); },
                 [](Array) { assert(false && "unsupported"); },
                 [](Function) { assert(false && "unsupported"); },
                 [](Train2) { assert(false && "unsupported"); },
                 [](Train3) { assert(false && "unsupported"); },
             },
             v);
  return ret;
}

}
