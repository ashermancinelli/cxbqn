#include "provides_helpers.hpp"

namespace cxbqn::provides {

// Find x in the runtime, and return the glyph at that index in the glyph string
O<Value> Glyph::call(u8 nargs, Args &args) {
  static const std::string glyphs{
      "+-×÷⋆√⌊⌈|¬∧∨<>≠=≤≥≡≢⊣⊢⥊∾≍⋈↑↓↕«»⌽⍉/⍋⍒⊏⊑⊐⊒∊⍷⊔!˙˜˘¨⌜⁼´˝`∘○⊸⟜⌾⊘◶⎉⚇⍟⎊"};
  auto x = args[1];
  auto it = std::find(runtime.begin(), runtime.end(), x);
  if (it == runtime.end())
    return CXBQN_NEW(Character, U'?');
  auto glyph = glyphs.begin();
  utf8::advance(glyph, std::distance(runtime.begin(), it), glyphs.end());
  return CXBQN_NEW(Character, (c32)utf8::next(glyph, glyphs.end()));
}

} // namespace cxbqn::provides
