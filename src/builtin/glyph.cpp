#include "provides_helpers.hpp"
#include <iostream>

namespace cxbqn::provides {

// Find x in the runtime, and return the glyph at that index in the glyph string
O<Value> Glyph::call(u8 nargs, Args &args) {
  static const std::string glyphs{
      "+-×÷⋆√⌊⌈|¬∧∨<>≠=≤≥≡≢⊣⊢⥊∾≍⋈↑↓↕«»⌽⍉/⍋⍒⊏⊑⊐⊒∊⍷⊔!˙˜˘¨⌜⁼´˝`∘○⊸⟜⌾⊘◶⎉⚇⍟⎊"};
  auto x = args[1];

  auto it = std::find(runtime.begin(), runtime.end(), x);

  // If we can't find it in the runtime, we want to use the native formatting
  // method
  if (it == runtime.end()) {
    std::stringstream ss;
    x->repr(ss);
    return CXBQN_NEW(Array, ss.str());
  }

  auto glyph = glyphs.begin();
  utf8::advance(glyph, std::distance(runtime.begin(), it), glyphs.end());
  return CXBQN_NEW(Character, (c32)utf8::next(glyph, glyphs.end()));
}

} // namespace cxbqn::provides
