include(${ROOT}/cmake/GenHelpers.cmake)

message(STATUS "Generating primitive l5 tests")
set(P_TESTS
    "(<'a')≡⊏\\\"abc\\\""
    "\\\"a\\\"≡⊏⥊˘\\\"abc\\\""
    "(<'c')≡2⊏\\\"abc\\\""
    "(<'c')≡¯1⊏\\\"abc\\\""
    "\\\"ccc\\\"≡2‿¯1‿2⊏\\\"abc\\\""
    "((3-˜↕5)⊸⊏≡2⊸⌽)↕5‿2"
    "(0‿3⥊0)≡⟨⟩⊏2‿3⥊↕6"
    "⟨3‿0,2‿1‿2⟩(×⟜5⊸+⌜´∘⊣≡⊏)⥊⟜(↕×´)6‿5"
    "(2‿0⥊0)≡⟨3‿¯1,⟨⟩⟩⊏4‿3⥊0"
    "5‿1(<⊸⊏≡⊏)↕6‿2"
    "⟨4‿0,1‿2‿3‿2‿1‿0⟩(+⌜´⊸(×⌜)≡⊏⟜(×⌜˜))+⌜˜↕5"
    "∧´1=≡¨(<⟨⟩)(↑¨∾↓¨)⟨@,+,<@,↕3⟩"
    "\\\"abc\\\"≡3↑\\\"abce\\\""
    "\\\"e\\\"≡¯1↑\\\"abce\\\""
    "\\\"\\\"≡0↑\\\"ab\\\""
    "(<⟜3⊸×↕5)≡5↑↕3"
    "(6⥊0)≡¯6↑↕0"
    "(≍↕3)≡1↑2‿3⥊↕6"
    "(↑⟜4≡⥊⟜0)↕3"
    "(≍\\\"abc\\\")≡(<1)↑2‿3↑\\\"abcd\\\""
    "(6⥊1)(↑≡⥊⟜⊑)2‿3⥊↕6"
    "(↕¨∘↕∘(1⊸+)≡↑∘↕)5"
    "(↑≡((↕4)≍¨2)⥊¨<)3‿2⥊\\\"abcdef\\\""
    "\\\"d\\\"≡3↓\\\"abcd\\\""
    "1‿2≡⟜(¯3⊸↓)○↕4‿2"
    "1‿1‿3‿2‿1≡≢(5⥊0)↓↕3‿2‿1"
    "(↓∘↕≡↕∘(1⊸+)+⟜⌽↑∘↕)5"
    "(↕3‿4)≡1↓¨⊏↕2‿3‿4"
    "(4+⌜○↕2)≡2↕↕5"
    "⟨⟩(↕≡⊢)4‿3⥊\\\"abcd\\\""
    "(0⊸↕≡(0≍˜1+≠)⊸⥊)↕6"
    "(7↕6‿0⥊\\\"\\\")≡0‿7‿0⥊\\\"\\\""
    "(»˜⊸≡∧«˜⊸≡)\\\"\\\""
    "\\\"a\\\"≡⟨⟩»\\\"a\\\""
    "⟨⟩≡\\\"a\\\"»⟨⟩"
    "\\\"aBC\\\"≡\\\"a\\\"»\\\"BCD\\\""
    "\\\"CDa\\\"≡\\\"a\\\"«\\\"BCD\\\""
    "\\\"d\\\"≡\\\"abcd\\\"«⟨4⟩"
    "((⊢⌜˜≠¨)≡(≠¨«⌜˜))\\\"\\\"‿⟨2,3⟩‿\\\"abcde\\\""
    "\\\"Zcab\\\"≡\\\"WXYZ\\\"«´\\\"ab\\\"‿\\\"c\\\"‿\\\"\\\""
    "\\\"dab\\\"≡'d'»\\\"abc\\\""
    "\\\"dab\\\"≡'d'<⊸»\\\"abc\\\""
    "(1⊸⌽≡⊏⊸«)'a'+⥊⟜(↕×´)4‿2"
    "¯2(⌽≡↑»⊢)'a'+⥊⟜(↕×´)4‿2"
    "6(↑≡»⟜(⥊⟜0)˜)↕4"
    "«˜⊸≡2‿3⥊\\\"abcdef\\\""
    "(»≡0⌈-⟜1)↕6"
    "(«≡1⊸⌽)↕6"
    "(»≡0⌈-⟜2)⥊⟜(↕×´)5‿2"
    "(«≡1⌽1⊸<⊸×)⥊⟜(↕×´)5‿2"
    "≡⟜⌽⟨⟩"
    "≡⟜⌽\\\"a\\\""
    "\\\"ba\\\"≡⟜⌽\\\"ab\\\""
    "(⌽≡(1-˜≠)(-○⊑∾1↓⊢)⚇1⊢)↕3‿2‿4"
    "≡⟜⌽↕↕3"
    "∧´5(⌽≡⊢)¨⟨\\\"\\\",⥊∞,↕5,↕0‿4,2‿0‿3⥊\\\"\\\"⟩"
    "∧´(\\\"bcdea\\\"≡⌽⟜\\\"abcde\\\")¨1+5×¯10‿¯2‿¯1‿0‿1‿6‿61"
    "∧´⟨1,0‿2,¯1‿1‿3⟩(⊑∘⌽≡(3⊸↑)⊸⊑)⚇¯1‿∞ 2‿3‿5⥊\\\"abcdef\\\""
    "(⟨⟩⊸⌽≡<)'a'"
    "0‿4≡/1‿0‿0‿0‿1‿0"
    "1‿1‿2≡/0‿2‿1"
    "≡⟜/⟨⟩"
    "\\\"aabbcc\\\"≡2/\\\"abc\\\""
    "\\\"\\\"≡4/\\\"\\\""
    "(6‿0⥊\\\"\\\")≡⟨5,1⟩‿⟨⟩/2‿0⥊\\\"\\\""
    "3‿3‿3‿2‿2‿1≡/˜3‿2‿1"
    "3‿3‿3‿2‿2‿1≡<⊸/3‿2‿1"
    "(≍1∾¨1‿2‿2)≡(↕¨/↕)2‿3"
    "(⟨⟩⊸/≡<)'a'"
    "⟨⟩(/≡⊢)↕10"
    "⟨⟩(/≡⊢)≍\\\"ab\\\""
    "⟨2,<3⟩(/≡⥊˜¨⟜≢/⊢)'a'+4‿2⥊↕8"
)

set(P_TEST_SOURCE "${BUILDDIR}/test_prim_l5.cpp")
set(P_SETPRIMS_TEST_SOURCE "${BUILDDIR}/test_prim_setprims_l5.cpp")
init_gen_file(${P_TEST_SOURCE})
init_gen_file(${P_SETPRIMS_TEST_SOURCE})

foreach(test ${P_TESTS})
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccx.bqn ${ROOT}/ext//bqn \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext//cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  string(REPLACE "\\`" "`" noesc "${test}")
  file(
    APPEND ${P_SETPRIMS_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${noesc}\");
  auto cu = ${compiled_test};
  auto ret = vm::run(cu);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dyncast<Number>(ret.v);
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
    auto cu = ${compiled_test};
    auto ret = vm::run(cu);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dyncast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
