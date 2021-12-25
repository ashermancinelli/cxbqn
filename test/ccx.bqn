#!/usr/bin/env bqn
# Modified version of https://github.com/mlochbaum/BQN/blob/master/src/cjs.bqn, which is under the ISC license (https://github.com/mlochbaum/BQN/blob/master/LICENSE)

args←•args
"Usage: ./ccx.bqn path/to/mlochbaum/BQN [-i] <(r|r0|r1|c|cc|f|e|p) or an expression>"!2≤≠args
return ← 1≡⊑args
args↓˜↩ return
path←(⊑args)∾"/src/"
args↓˜↩1
Import ← {𝕨•Import path∾𝕩}
FChars ← {𝕨•FChars path∾𝕩}
FLines ← {𝕨•FLines path∾𝕩}

split ← •Import "../lib/strings/split.bqn"
replaceall ← •Import "../lib/strings/replaceall.bqn"

F ← •Repr  # Format number
# Escape the special characters that appear in BQN sources.
Esc←{
  in ← (@+0‿9‿10‿13)∾"'"""   # Null, Tab, LF, CR, and quotes
  out ← "0tnr"               # Whitespace characters changed to letters
  i ← in⊐𝕩
  𝕩 ↩ i ⊏⟜out⌾((i<≠out)⊸/) 𝕩 # Replace
  ∾(i<≠in) /⟜"\"⊸∾¨ 𝕩        # Insert \
}

OStr ← "CXBQN_NEW(Array,U"""∾Esc∾""")"˙  # A BQN string
OChr ← {"CXBQN_NEW(Character,U'"∾(Esc⥊𝕩)∾"')"} # A BQN character
ONum ← {s←"-"/˜𝕩<0 ⋄ ∞⊸=∘|◶⟨"CXBQN_NEW(Number,"∾")"∾˜s∾F∘| ⋄ "CXBQN_NEW(Number,"∾s∾"1.0/0.0)"⟩𝕩} # Format number
OAny ← ≡◶⟨@⊸≤◶ONum‿OChr, OStr, ⊑⟩

List ← (0<≠)◶⟨"",1↓·∾","⊸∾¨⟩
ShortList ← {"{"∾(List𝕩)∾"}"}
LongList ← {"{"∾(List𝕩)∾"}"}
MakeList ← (≠∘⊢>4˙)◶ShortList‿LongList
Li ←  {"i32" MakeList F¨𝕩}
_Lo ← {"B"   MakeList 𝔽¨𝕩}


glyphs ← Import "glyphs.bqn"
_getComp ← { (4+2×useInd)↑ <∘⊢∾˜ 5↑ (𝕗 Import "c.bqn"){𝔽} }
useInd ← "-i"≡⊑args ⋄ args↓˜↩useInd
Comp ← ((<"runtime["∾F∾"]"˙)¨↕≠∾glyphs) glyphs _getComp ⊢
J ← ∾∾⟜(@+10)¨

Fout ← {
  ((≠𝕩)↑⟨Li ⋄ OAny _Lo ⋄ =◶⟨ONum,Li _Lo⟩ _Lo _Lo ⋄ (Li 2⊸↑) _Lo ⋄ Li _Lo ⋄ OStr⟩) {𝕎𝕩}¨ 𝕩
}

Frun ← 1⊸Fout
Long ← {¯2↓∾𝕩∾¨<","∾@+10}
LFC ← Long∘Fout∘{o←Comp𝕩}

RT ← {
  src‿need‿inputs←𝕩Import"pr.bqn"
  pr←"runtime_0"‿"provide"{(∾𝕨<⊸(<∘{∾""‿𝕨‿"["‿𝕩‿"]"}⟜F¨)⟜(↕≠)¨𝕩)⊏˜(∾𝕩)⊐∾need}○((-1+1=𝕩)⊸↑)inputs
  Long Fout pr need _getComp src
}
CArg ← {J (¯5⊸↓∾𝕩˙)⌾⊑ FLines "c.bqn"}
SVG ← {∾⟨"Modify←GetHighlights←⊢⋄"⟩∾ FChars∘∾⟜".bqn"¨ "../svg"‿𝕩}

r←(⊑"r"‿"r0"‿"r1"‿"c"‿"cc"‿"f"‿"e"‿"p"⊐⊏)◶⟨
  RT∘2, RT∘0, RT∘1
  {𝕩⋄LFC CArg "⟨"∾"⟩"«∾","⊸∾¨'"'(⊣∾∾˜)¨glyphs}
  {𝕩⋄LFC "{"∾"}"∾˜CArg"𝕩"}
  {𝕩⋄LFC FChars "f.bqn"}
  {𝕩⋄LFC SVG "e"}
  {𝕩⋄LFC SVG "p"}
  ∾LFC¨
⟩ args

# Split into lines
bc‿consts‿blk‿bod ← (@+10) Split r

# Just replace the CXBQN_NEWs in the blocks as we don't need them there
blk2←⟨")"⟩‿⟨""⟩ ReplaceAll ⟨"CXBQN_NEW(Number,"⟩‿⟨""⟩ ReplaceAll blk

# No comma
NC ← {1⊸↓⌾⌽""∾𝕩}

•Show ¨consts‿blk2‿bc‿bod

•Out "[=] {
  std::vector<O<Value>> c"∾(NC consts)∾";
  std::vector<BlockDef> bds"∾(NC blk2)∾";
  auto cu = make_observer(new CompUnit{
      ._bc"∾(NC bc)∾",
      ._consts{CXBQN_NEW(Array,c.size())},
      ._blocks{},
      ._bodies"∾(NC bod)∾"},
      });
  for (auto& bd : bds)
    cu->_blocks.emplace_back(bd);
  cu->_consts->values = std::move(c);
  cu->_consts->shape.push_back(c.size());
  GC::register_ptr(cu.get());
  return cu;
}()"
