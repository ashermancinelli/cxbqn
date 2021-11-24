⟨
  T # Run test
  R # Report failures
  f # Number of failures
⟩⇐

f←0
T ← {
  r←𝕨=•BQN 𝕩
  •Show ""∾r⊑"F."
  f↩f+¬r
}

R ← {
  𝕩
  #•Out (0=f)⊑⟨
  #  "-- Got "∾•Fmt f∾" failures!"
  #  "-- All tests passed."
  #⟩
  f
}
