include(${ROOT}/cmake/GenHelpers.cmake)

message(STATUS "Generating primitive l6 tests")
set(P_TESTS
    "≡⟜(∾⥊¨)\\\"abc\\\""
    "(∾´≡∾)\\\"ab\\\"‿\\\"cde\\\"‿\\\"\\\""
    "\\\"abc\\\"≡∾\\\"ab\\\"‿'c'‿\\\"\\\""
    "1‿2‿3‿4‿6‿9≡∾(⊢×≠↑↓)1+↕3"
    "(≡⟜∾∧≡⟜(∾<))<4"
    "⟨1‿4,⥊2⟩((∾⋆⌜⌜)≡⋆⌜○∾)⟨2‿3‿4,⟨⟩,⥊5⟩"
    "(6‿3⥊0)≡∾⟨2‿3,3,3‿3⟩⥊¨0"
    "\\\"abcd\\\"≡\\\"abc\\\"∾'d'"
    "\\\"abcd\\\"≡\\\"abc\\\"∾<'d'"
    "(↕4‿3)≡(↕3‿3)∾3∾¨↕3"
    "(∾˜≡·¯1⊸(×´∘↓∾↑)∘≢⊸⥊≍˜)2‿3⥊\\\"abcdef\\\""
    "(∾´≡∾)⟨3‿2‿1,0‿2‿1⟩⥊¨<↕6"
    "⟨1‿2,⥊0,⥊3⟩≡⊔1‿0‿0‿2"
    "⟨⟩≡⊔5⥊¯1"
    "≡⟜⊔⟨⟩"
    "(⊔≡⥊¨¨∘⊔∘⊑)⟨1‿0‿0‿2⟩"
    "(≍⍟2∘<¨⌽↕3‿2)≡⊔⟨2‿1‿0,0‿1⟩"
    "(↕0‿0)≡⊔⟨⟩‿⟨⟩"
    "(⊔≡·≍⍟2∘<·∾⌜´/∘(0⊸=)¨)⟨0‿¯1‿0‿0,¯1‿0‿0⟩"
    "(0‿0‿1↑⌜≍⍟2∘<∘⥊¨1‿0)≡⊔⟨2,1‿0⟩"
    "(0‿0‿1↑⌜≍⍟2∘(<0‿0‿0⊸∾)¨1‿0)≡⊔0‿0⊸↓¨⟨2,1‿0⟩"
    "4‿3‿2(⋈≡·(≠¨⋈∾)/⊸⊔)\\\"abcdefghi\\\""
    "⟨⟩≡(3⥊¯1)⊔\\\"abc\\\""
    "⟨⟩≡(2⥊¯1)⊔\\\"a\\\""
    "(≍˘1‿1‿4<∘⥊⎉1 16‿4+⌜↕4)≡2↓⟨3‿2,¯1‿0‿¯1⟩⊔2‿3‿4⥊↕24"
    "⥊⚇0⊸≡○⊔⟜(⥊<)1‿2‿2‿¯1‿0"
    "(∾↕¨∘≢⊸⊔)⊸≡ 3‿2‿4⥊↕24"
    "-⟜'a'⊸(⊔≡⊔○⥊)\\\"acc\\\"≍\\\"bac\\\""
    "(2‿1/⟨↕0‿1,1‿1⥊3⟩)≡2⊔⥊3"
    "((<=·↕1⊸+)≡·≢¨<¨⊸⊔⟜(<@))2‿1‿3"
    "(1‿3/⟨\\\"a\\\",\\\"\\\"⟩)≡0‿¯1‿4⊔\\\"ab\\\""
    "¯1⊸↓⊸(≡○(⊔⟜\\\"ab\\\"))2‿3‿1"
    "(≍1‿1‿0≍∘/⟜≍¨\\\"bac\\\")≡⟨0,1‿0‿3⟩⊔\\\"ab\\\""
    "(⌽˘≡·∾⟨2‿2,1‿0‿1⟩⊸⊔)\\\"ab\\\"≍\\\"cd\\\""
    "2‿0‿4≡\\\"abcd\\\"⊐\\\"cae\\\""
    "⟨1⟩≡\\\"abcd\\\"⊐\\\"b\\\""
    "(<2)≡\\\"cdef\\\"⊐'e'"
    "(<3)≡⊐⟜(3⊸⊏)\\\"abcd\\\""
    "(5⌊3+↕5)≡⊐⟜(3‿0‿0+⚇1⊢)↕5‿2‿1"
    "0‿0‿1‿0‿2≡⊐\\\"ccacb\\\""
    "0‿0‿1‿0‿2≡⊐≍˜˘\\\"ccacb\\\""
    "≡⟜⊐⟨⟩"
    "1‿0‿0‿1≡\\\"acef\\\"∊\\\"adf\\\""
    "(∊⟜(↕2)≡<⟜2)3⋆⌜○↕5"
    "(<1)≡3‿4‿5∊4+⌜○↕3"
    "('0'≠\\\"11010001\\\")≡∊\\\"abacbacd\\\""
    "(↑⟜1≡⟜∊⥊⟜∞)9"
    "(⥊⟜1≡∊∘↕)6"
    "≡⟜∊⟨⟩"
    "≡○∊⟜(≍˜˘)\\\"abcadbba\\\""
    "≡⟜⍷⟨⟩"
    "\\\"ba\\\"≡⍷\\\"baa\\\""
    "0‿1‿0‿0≡\\\"abc\\\"⍷\\\"aabcba\\\""
    "(0‿1≍0‿0)≡(1‿2≍4‿5)⍷3‿3⥊↕9"
    "(↕3‿0)≡⍷⟜(≍˘)\\\"abc\\\""
    "'a'(=≡⍷)\\\"abc\\\""
    "(⌽¨≡⍉)↕2⥊3"
    "(⍉≡<)'a'"
    "∧´⍉⊸≡¨⟨<'a',\\\"a\\\",\\\"abc\\\",\\\"\\\"⟩"
    "(↕4)(-˜⌜˜≡·⍉-⌜)↕3‿2"
    "(2×↕3)≡0‿0⍉6+⌜○↕3"
    "(⟨⟩⊸⍉≡<)4"
    "⟨⟩(⍉≡⊢)<4"
    "(2‿0‿1⥊⟨⟩)≡1‿2‿0‿1⍉↕↕4"
    "(↕1‿2‿0‿3)≡2<⊸⍉↕↕4"
    "0⊸⍉⊸≡2‿3⥊↕6"
    "2‿0‿3‿1‿4≡⍋\\\"bdace\\\""
    "5‿2‿4‿3‿0‿1≡⍋↓\\\"deabb\\\""
    "(⍋≡⍒)⟨\\\"\\\",↕0,0↑<\\\"abc\\\"⟩"
    "(⍋≡↕∘≠)4‿0⥊@"
    "(⍒≡⌽∘↕∘≠)⟨¯∞,¯1.5,π,∞,'A','a','b'⟩"
    "(⍒≡⌽∘↕∘≠)⟨↕0,¯1.1,¯1,¯1‿¯∞,¯1‿0,¯1‿0‿0,¯1‿∞,0,6⥊0,1e¯20,1,1+1e¯15⟩"
    "(⍒≡⌽∘↕∘≠)(<∾⟨↕0,1,1‿1,2‿1‿1,2‿1,2,1‿2,2‿2,3⟩⥊¨<)'a'"
    "(⍋≡↕∘≠)⥊⍉(↕5)⥊⟜1⊸⥊⌜1‿'b'"
    "(⊢≡○⍋(0‿1+≠)⥊⊢)⟨¯2,'a',1,'f'⟩"
    "⟨1,2,3,1‿2,2‿1,1‿3,2‿2,3‿1⟩(⥊⊸(≠∘⊣∾˜¯1⊸⊑⊸(⌊∾⊣)∾×´⊸⌊)⌜≡○(⍋⥊)⥊⌜⟜(+\\`∘≠⟜(↕6)¨))↕4"
    "((⥊˜-⥊⟜2‿0)∘≠≡⍋+⍒)2/↕5"
    "\\\"edcba\\\"≡∨\\\"bdace\\\""
    "(↕7)≡∧⍋|⟜⌽1+↕7"
    "⟨1,3,∞,'e','i'⟩ (⍋≡≠∘⊣(⊣↓⊢⍋⊸⊏+\\`∘>)⍋∘∾) (2÷˜↕8)∾\\\"aegz\\\""
    "⟨'z','d',1‿0,0⟩ (⍒≡≠∘⊣(⊣↓⊢⍋⊸⊏+\\`∘>)⍒∘∾) (2÷˜↕8)∾\\\"aegz\\\""
    "(<∘⌈≡(↕6)⊸⍋)2.5"
    "(<1)≡(↕2‿3)⍋1+↕3"
    "(<0)≡\\\"abc\\\"⥊⊸⍒○<≍\\\"acc\\\""
)

set(P_TEST_SOURCE "${BUILDDIR}/test_prim_l6.cpp")
set(P_SETPRIMS_TEST_SOURCE "${BUILDDIR}/test_prim_setprims_l6.cpp")
init_gen_file(${P_TEST_SOURCE})
init_gen_file(${P_SETPRIMS_TEST_SOURCE})

foreach(test ${P_TESTS})
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext//bqn -i \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext//cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  string(REPLACE "\\`" "`" noesc "${test}")
  string(REPLACE "¯" "-" minus "${compiled_test}")
  file(
    APPEND ${P_SETPRIMS_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${noesc}\");
  CompileParams p( ${minus} );
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dynamic_pointer_cast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
  file(
    APPEND ${P_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
    spdlog::critical(\"test='{}'\", \"${noesc}\");
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
    CompileParams p{ ${compiled_test} };
    auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dynamic_pointer_cast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
