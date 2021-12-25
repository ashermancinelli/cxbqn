marksplit←•Import "detail/marksplit.bqn"

# Split string 𝕩 on occurrences of separator 𝕨, removing the separators
Split ← (0<≠∘⊢)◶⟨
  ≍○<⊢
  (1+`⊢)⊸((1-˜×)∾¯1⊏⊣)´∘MarkSplit⍟(0<≠∘⊢) ⊔ ⊢
⟩

split
