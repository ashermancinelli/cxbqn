include(${ROOT}/cmake/GenHelpers.cmake)
message(STATUS "Generating undo tests")
set(S_TESTS
    "∧´{𝕩≡𝕩⁼𝕩}¨⟨¯∞,3,@,'⁼',↕4⟩"
    "3⁼4"
    "2‿3⁼2‿3.1"
    "∧´ {(𝕎≡𝕎⁼)𝕩}⟜¯0.3‿0‿8¨ +‿-‿÷‿¬‿⊢‿⊣‿⌽"
    "-⁼ 'a'"
    "×⁼ 5"
    "(√√⁼)⊸≡ 0‿0.4‿π‿1e9‿∞"
    "(⋆⁼⋆)⊸≡ ↕4"
    "1e¯14>|1-⋆+´⋆⁼1(⊢÷«)1+↕11"
    "∧´ {𝕩≡6𝕎6𝕎⁼𝕩}⟜1‿2‿3¨ +‿-‿×‿÷‿√‿∧‿¬‿⊢"
    "'a' ≡ 3+⁼'d'"
    "'d'-⁼'a'"
    "0.3‿1.01‿π(⋆⁼⌜≡÷˜⌜○(⋆⁼))0‿2‿5.6‿∞"
    "(⊢≡⊣⁼˜)\\\"abcd\\\""
    "\\\"ab\\\"⊣⁼\\\"ac\\\""
    "(<⁼<)¨⊸≡⟨0,⟨⟩,\\\"abc\\\"⟩"
    "(/⁼/)⊸≡1‿0‿2‿4"
    "⟨⟩≡/⁼⟨⟩"
    "(3⊸⌽≡2⌽⁼⊢)↕5"
    "((≢⍉⁼)≡¯1⌽≢)↕↕4"
    "≡´⍉⍟¯1‿2⥊⟜(↕×´)2‿3‿3"
    "2‿1(⊢≡⊣⍉⍉⁼)⥊⟜(↕×´)2‿3‿1‿4"
    "∧´ {6(𝕎˜⁼≡𝕎⁼)𝕩}⟜¯0.8‿0‿3¨ +‿×‿∧"
    "+˜⁼7"
    "∨˜⁼0.75"
    "+´∊⟨√,×˜⁼,∧˜⁼⟩{𝕎𝕩}⌜0‿2‿∞"
    "∧´ -‿÷‿⋆ {3(𝕎˜⁼≡𝕏)2‿π∾⋆2}¨ +‿×‿√"
    "16√˜⁼2"
    "4‿2‿0(¬˜⁼≡¯1++)1‿2‿9"
    "-¨⁼ 2"
    "-⌜⁼ 2"
    "-˘⁼ 2"
    "-˘⁼ <2"
    "-\\`⁼ 2"
    "0-´⁼ 2"
    "(∾˜ ≡ ·(<⌜⁼∾<¨⁼)<¨) \\\"abcd\\\""
    "\\\"ab\\\"‿\\\"abc\\\"≡1⌽⁼¨\\\"ba\\\"‿\\\"bca\\\""
    "(2-=⌜˜↕2)≡/˘⁼0‿1‿1≍0‿0‿1"
    "2(⌽˘⁼≡·⍉⌽⁼⟜⍉)≍\\\"abcde\\\""
    "(4⥊1) ≡ +\\`⁼ 1+↕4"
    "⟨⟩ ≡ !\\`⁼⟨⟩"
    "(-⟜» ≡ +\\`⁼) 2|⌊×⌜˜π+↕5"
    "(5⥊2)≡2÷\\`⁼2⋆-↕5"
    "(0‿1‿1×⌜⥊˜4)≡(↕4)+\\`⁼3‿4⥊↕12"
    "(↕3)+\\`⁼3‿4⥊↕12"
    "(÷¬)⁼ 4"
    "⊢∘√⁼ 2"
    "(⌽/1‿3)≡(·+\\`⌽)⁼↕4"
    "(⌽⊸/1‿3)≡(⌽·-\\`⌽)⁼↕4"
    "(¯1‿0+⌜\\\"BQN\\\")≡(1⌽⍉)⁼3‿2⥊\\\"PQMNAB\\\""
    "(3×·√2+¬)⁼6"
    "(3⊸√+⟜7)⁼2"
    "5×⟜¬⁼10"
    "(√-2{𝔽})⁼1"
    "(√-2˙)⁼1"
    "21(1+÷)⁼8"
    "(2⊸⌽ ≡ 2⊸(-⊸⌽)⁼)\\\"abcde\\\""
    "¯2 ÷˜○¬⁼ ¯1"
    "1e¯12>|16- 2 ÷˜○(⋆⁼)⁼ 4"
    "(+\\`⌾⌽⁼≡+\\`⁼⌾⌽) ↕4"
    "×˜⍟3⁼256"
    "√⊘-{𝕗⁼≡6𝕗⁼⊢} ¯3‿2"
    "∧´ {(𝕎≡𝕎⁼⁼)𝕩}⟜2‿4‿1¨ /‿⌽‿<"
    "/⁼⁼2‿3‿0"
    "/⍟¯1⁼2‿3‿0"
)

set(S_ANS
    "1"
    "!"
    "!"
    "1"
    "!"
    "!"
    "1"
    "1"
    "1"
    "1"
    "1"
    "3"
    "1"
    "1"
    "!"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "3.5"
    "0.5"
    "1"
    "1"
    "4"
    "1"
    "!"
    "!"
    "!"
    "!"
    "!"
    "!"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "1"
    "!"
    "0.75"
    "4"
    "1"
    "1"
    "1"
    "-1"
    "1"
    "-1"
    "9"
    "9"
    "3"
    "1"
    "4"
    "1"
    "1"
    "2"
    "1"
    "1"
    "!"
    "!"
)

set(S_TEST_SOURCE ${BUILDDIR}/test_undo.cpp)
init_gen_file(${S_TEST_SOURCE})

foreach(test ans IN ZIP_LISTS S_TESTS S_ANS)
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccx.bqn ${ROOT}/ext//bqn \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext//cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  string(REPLACE "¯" "-" cesc "${compiled_test}")
  string(REPLACE "\\`" "`" tesc "${test}")
  file(
    APPEND ${S_TEST_SOURCE}
    "
TEST_CASE(\"${tesc}\") {
  spdlog::critical(\"test='{}', ans='{}'\", \"${tesc}\", \"${ans}\");
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  auto cu =
    ${cesc}
    ;
  "
  )
  if("${ans}" STREQUAL "!")
    file(
      APPEND ${S_TEST_SOURCE}
      "
    REQUIRE_THROWS(vm::run(cu));
}
"
    )
  else()
    file(
      APPEND ${S_TEST_SOURCE}
      "
  auto ret = vm::run(cu);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dyncast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
"
    )
  endif()
endforeach()
