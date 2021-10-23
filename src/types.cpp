#include <types.hpp>

namespace cxbqn::types {

#define EXPLICIT_INSTANTIATE(TYPE) template struct Array< TYPE >;

CXBQN_FOR_ALL_TS(EXPLICIT_INSTANTIATE);

#undef EXPLICIT_INSTANTIATE

}
