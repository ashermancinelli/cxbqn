
•Show "foo"
#•Show •args
•Exit 1

DefaultSuites ← {
  d ← "suites/always/"
  always ← d⊸∾¨•file.List d

  hascuda ← +´⟨"CXBQN_CUDA"⟩⊸⍷⊑¨•cxbqn.config

  d ↩ "suites/cuda/"
  cuda ← d⊸∾¨•file.List d

  always∾(hascuda⊑⟨⟩‿cuda)
}

suites←1

•Out "Suites: "
•Show suites

# Index of test
i←0

# Number of failures
f←0

# Failure string to be printed at the end of the test run in case of failures
fs←""

# Run a single test suite.
# This would use headers if CXBQN supported them.
T ← {
  i↩i+1
  a‿tt←𝕩
  c←a≡r←•BQN tt
  f↩f+¬c
  fs↩fs∾c⊑⟨(10+@)∾"test '"∾tt∾"' failed: expected: '"∾(•Fmt a)∾"', got: '"∾(•Fmt r)∾"'", ""⟩
  "" •Out ""∾c⊑"F."
  f
}

# Run all test cases in each test suite
{ •Out "Running suite "∾𝕩⋄T ¨ •Import 𝕩} ¨ suites

•Out ""

•Out (×f)⊑⟨
  "All tests passed."
  "Got "∾(•Fmt f)∾" failures:"∾fs
⟩
