marksplit←•Import "marksplit.bqn"

# Return mask of non-overlapping positions in 𝕩 where 𝕨 is found
# Like 𝕨⍷𝕩 but same length as 𝕩 and suppressing overlaps (leftmost wins)
Locate ← ⊑ MarkSplit
