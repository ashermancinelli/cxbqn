include(${ROOT}/cmake/GenHelpers.cmake)

message(STATUS "Generating under tests")
set(P_TESTS
    "(⊑≡⊑⌾⊢) ⟨↕3,2,<\\\"abc\\\"⟩"
    "3 (+≡+⌾⊣) 4"
    "(¯2⊸↓ ≡ 2⊸↓⌾⌽) ↕6"
    "(1⊸↓⌾⍉ ≡ 1⊸↓˘) ↕3‿3"
    "7(⥊⌾(<˘)≡·<˘⁼⥊⟜(<˘))3‿3⥊↕9"
    "\\\"abcd\\\" (⊣≡»⌾≍) ↕4"
    "(⌽∘|⊸/4‿¯3) ≡ ↕∘≠⊸-⌾(3⊸⌽)↕7"
    "\\\"bbcd\\\" ≡ 1⊸+⌾⊑ \\\"abcd\\\""
    "(<∘- ≡ -⌾⊑) 4"
    "(⌽⌾⊏ ≡ ⌽⊸≍˝) \\\"abc\\\"≍\\\"def\\\""
    "1 ≡ \\\"cd\\\"‿\\\"ab\\\"⊸⊐⌾< \\\"ab\\\""
    "(0‿1+⌜0‿4‿2) ≡ ⍋∘⍋⌾⥊ \\\"apl\\\"≍\\\"bqn\\\""
    "2 (⌽⌾⥊ ≡ 12|+) ⥊⟜(↕×´)6‿2"
    "↕∘≠⊸+{𝔽≡𝔽¨⌾↑} \\\"abcde\\\""
    "2⊸+{𝔽≡𝔽¨⌾↓} \\\"abcde\\\""
    "(⌽⍒⌊2÷˜↕7) ≡ ⌽˘⌾(⌊‿2⥊⊢)↕7"
    "¯1‿0‿1‿3 ≡ -⟜(+´÷≠)⌾(3⊸↑)↕4"
    "\\\"adcb\\\" ≡ ⌽⌾(1⊸↓)\\\"abcd\\\""
    "5‿6‿3‿0 ≡ (5‿3‿1⌾(0‿0⊸⍉)4‿3⥊0) +´∘×⎉1‿∞ 1+↕3"
    "\\\"AbcD\\\" ≡ ('A'-'a')⊸+⌾(1‿0‿0‿1⊸/)\\\"abcd\\\""
    "\\\"AbcD\\\" ≡ \\\"ABCD\\\"⊣⌾(1‿0‿0‿1⊸/)\\\"abcd\\\""
    "(1⊸⌽ ≡ 2⊸⌽⌾(2⊸/)) ↕5"
    "\\\"bdca\\\" ≡ 1⊸⌽⌾(1‿3‿0⊸⊏)\\\"abcd\\\""
    "((¯1⋆2∧⌜○(⌽0=↕)3)⊸× ≡ -⌾(1‿2⊑⊢))↕2‿3"
    "((0‿3≍1‿2)⊸+ ≡ ⟨1,2‿3⟩⊸+⌾(⟨1‿0,⟨1‿1,0‿1⟩⟩⊸⊑))↕2‿2"
    "(1+↕3) ≡ 1⊸↓⌾(@⊢·⊑<)↕4"
    "\\\"210abc\\\" ≡ ⌽⌾((2÷˜≠)⊸↑)\\\"012abc\\\""
    "\\\"bac\\\"‿'d' ≡ ⌽⌾(2↑⊑)\\\"abc\\\"‿'d'"
    "(⌽¨⌾(<2‿3⊸⊏) ≡ ⌽⌾(2‿3⊸⊏)) \\\"abcdef\\\""
    "\\\"bdca\\\" ≡ 1⊸⌽⌾(1‿3‿0˙⊏⊢)\\\"abcd\\\""
    #"3 % 1⊸+⌾-4"
    #"20 % ⌊0.5+ 4+⌾(⋆⁼)5"
    #"2 % ⊢⌾2 3"
    #"-2 % ⊢⌾(2∘-) 3"
    "∘‿+ ≡ ⊢⌾∘‿+ 1"
)

set(P_TEST_SOURCE "${BUILDDIR}/test_under.cpp")
init_gen_file(${P_TEST_SOURCE})

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
    APPEND ${P_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${noesc}\");
  CompileParams p( ${minus} );
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies, p.source_indices.value(), p.source_str);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dynamic_pointer_cast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
