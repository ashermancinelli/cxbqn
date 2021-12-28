#include "provides_helpers.hpp"
#include <iostream>

namespace cxbqn::provides {

// Find x in the runtime, and return the glyph at that index in the glyph string
O<Value> Glyph::call(u8 nargs, Args &args) {
  static const std::string glyphs{
      "+-×÷⋆√⌊⌈|¬∧∨<>≠=≤≥≡≢⊣⊢⥊∾≍⋈↑↓↕«»⌽⍉/⍋⍒⊏⊑⊐⊒∊⍷⊔!˙˜˘¨⌜⁼´˝`∘○⊸⟜⌾⊘◶⎉⚇⍟⎊"};
  auto x = args[1];
  if (t_Namespace == type_builtin(x)) {
    auto xx = dyncast<Namespace>(x);
    std::stringstream ss;
    x->repr(ss);
    return CXBQN_NEW(Array, ss.str());
  }
  auto it = std::find(runtime.begin(), runtime.end(), x);
  if (it == runtime.end())
    return CXBQN_NEW(Character, U'?');
  auto glyph = glyphs.begin();
  utf8::advance(glyph, std::distance(runtime.begin(), it), glyphs.end());
  return CXBQN_NEW(Character, (c32)utf8::next(glyph, glyphs.end()));
}

} // namespace cxbqn::provides
