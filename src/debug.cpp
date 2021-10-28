#include <cxbqn/debug.hpp>

namespace cxbqn::debug {

void scope(types::Scope* sc) {
  CXBQN_DEBUG("Scope{");
  vdbg("  ", sc->vars);
  CXBQN_DEBUG("}");
}

}
