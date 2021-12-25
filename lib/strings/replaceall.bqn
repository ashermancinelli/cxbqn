locate←•Import "detail/locate.bqn"

# Replace each instance of a string in old with the corresponding
# string in new.
# Instances are non-overlapping, and earlier ones take precedence.
# TODO: headers
ReplaceAll ← {
  ⟨old, new⟩ ← 𝕨
  str ← 𝕩
  ! (≠new) ≡ l ← ≠old
  match ← 1-˜ (l+1)|⌊´ (↕⊸-l) × old Locate¨ <str
  cont ← (-⟜1⌈≤⟜1×⊢)` match ⊏ (≠¨old)∾0
  keep ← ≍○<⟜(⊏⟜str) / 0=cont
  insert ← (new⊏˜⊏⟜match)⊸(≠¨⊸/≍○<∾∘⊣) / (0⊸<∧»⊸≤) cont
  ⍋⊸⊏´ keep ∾¨ insert
}

replaceall
