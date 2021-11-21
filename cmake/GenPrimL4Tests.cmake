
include(${ROOT}/cmake/GenHelpers.cmake)

message(STATUS "Generating primitive l4 tests")
set(P_TESTS
    "\\\"a\\\"≡⋈'a'"
    "({⟨𝕩⟩}≡⋈)'a'‿2"
    "\\\"abc\\\"‿1≡\\\"abc\\\"⋈1"
    "⋈´⊸≡\\\"ab\\\""
    "∧´≡⟜>¨⟨1,<'a',<∞,↕5,5‿3⥊2⟩"
    "2‿3‿2≡≢>↕2‿3"
    "2‿3≡>⟨<2,3⟩"
    "((4⥊2)⊸⥊≡(>2‿2⥊·<2‿2⥊⊢))\\\"abcd\\\""
    "(⊢≡>∘<)5‿3⥊↕15"
    "(⊢≡(><¨))5‿3⥊↕15"
    "(⥊≡≍)'a'"
    "(⥊≡≍)<'a'"
    "(1‿2⊸⥊≡≍)\\\"ab\\\""
    "1‿2≡1≍2"
    "2‿1(≍≡2‿2⥊∾)4‿3"
    "(≍⟜<≡≍˜)'a'"
    "(≍˘˜⥊˘1‿5‿9)≡⌽⎉2⊸+⥊⟜(↕×´)3‿2‿1"
    "(<0)≡≡˘0"
    "(<1)≡≡˘<0"
    "(2⥊<<\\\"ab\\\") ≡ ⋈˜˘<\\\"ab\\\""
    "(3⥊0) ≡ {-}=˘↕3"
    "(↕4)(×⌜≡×⎉0‿2)↕5"
    "(↕4)(⋆˜⌜˜≡⋆⎉∞‿¯4)↕5"
    "(⟨2⟩⊸∾⍟(2‿2⥊0‿1‿1‿1)2‿3)≡≢¨≍⎉(⌊○=)⌜˜⟨↕3,2‿3⥊↕6⟩"
    "(2=⌜○↕3)≡(2‿4⥊\\\"abc\\\")≡⎉1(2‿3‿4⥊\\\"abc\\\")"
    "⟨0,0⟩≡(2‿4⥊\\\"abc\\\")≡⎉¯1(2‿3‿4⥊\\\"abc\\\")"
    "(-≡-⚇¯1)5"
    "⟨5,⟨15,1⟩⟩≡+´⚇1⟨⟨3,2⟩,⟨⟨4,5,6⟩,⟨1⟩⟩⟩"
    "5‿6‿15≡∾´+´⚇1⟨⟨0,1⟩,⟨⟨⟩⟩⟩⥊⊸∾⚇¯2‿1⟨⟨2,3⟩,⟨4,5,6⟩⟩"
    "(5⥊1)≡(↕5)=○=⚇0{≍}"
    "4≡2+⍟¯1 6"
    "(2×↕7)≡2+⍟(¯3+↕7)6"
    "(3⌊↕5)≡{i←0⋄r←{i+↩1⋄1+𝕩}⍟(↕4)𝕩⋄r∾i}0"
    "(+⌜˜≡·>1+⍟⊢⊢)↕5"
    "0‿1‿3‿6‿10≡+\\`↕5"
    "(-0‿1‿3‿6‿10)≡-\\`↕5"
    "((0∾¨↕3)≍3⥊0)≡≡\\`↕2‿3"
    "⟨⟩≡×\\`⟨⟩"
    "≡⟜(!∘0\\`)3‿0‿2⥊\\\"\\\""
    "2‿3‿5‿8‿12≡2+\\`↕5"
    "(2⋆1‿2‿6×⌜0‿2)≡3‿4⋆\\`3+⌜○↕2"
)

set(P_TEST_SOURCE "${BUILDDIR}/test_prim_l4.cpp")
set(P_SETPRIMS_TEST_SOURCE "${BUILDDIR}/test_prim_setprims_l4.cpp")
init_gen_file(${P_TEST_SOURCE})
init_gen_file(${P_SETPRIMS_TEST_SOURCE})

foreach(test ${P_TESTS})
  execute_process(
    COMMAND
      ${BASH} -c
      "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext//bqn -i \"${test}\""
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
  CompileParams p( ${compiled_test} );
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies, p.source_indices.value(), p.source_str);
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
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dynamic_pointer_cast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
