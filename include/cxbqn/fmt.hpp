#include <cxbqn/types.hpp>
#include <iostream>

namespace cxbqn::fmt {

using namespace cxbqn::types;

std::ostream& repr(std::ostream &os, Value *v);
std::ostream& operator<<(std::ostream &os, Block b);
std::ostream& operator<<(std::ostream &os, Body b);

}
