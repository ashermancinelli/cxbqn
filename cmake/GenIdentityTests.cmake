include(${ROOT}/cmake/GenHelpers.cmake)
message(STATUS "Generating identity tests")
set(S_TESTS
"∧´ {𝕩≡𝕎´⟨⟩}´¨ ⟨+‿0,-‿0,×‿1,÷‿1,∨‿0,∧‿1⟩"
"∧´ {𝕩≡𝕎´⟨⟩}´¨ ⟨⋆‿1,¬‿1,⌊‿∞,⌈‿¯∞⟩"
"∧´ {𝕩≡𝕎´⟨⟩}´¨ ⟨≠‿0,=‿1,>‿0,≥‿1⟩"
"√´↕0"
"|´↕0"
"⊢´\\\"\\\""
"⊣´\\\"\\\""
"∾´⟨⟩"
"≍´⟨⟩"
"∧´ {(3‿1⥊𝕩)≡𝕎˝0‿3‿1⥊\\\"\\\"}´¨ ⟨+‿0,-‿0,×‿1,÷‿1,∨‿0,∧‿1,⋆‿1,¬‿1,⌊‿∞,⌈‿¯∞,≠‿0,=‿1,>‿0,≥‿1⟩"
"∾˝\\\"\\\""
"(∾˝(↕5)⥊\\\"\\\") ≡ (≠⟜1⊸/↕5)⥊\\\"\\\""
"(∾˝¨≡⥊¨) (≍⥊0˙)⌜˜0‿2‿5"
"⌽˝0‿3⥊⟨⟩"
)

set(S_ANS
"1"
"1"
"1"
"!"
"!"
"!"
"!"
"!"
"!"
"1"
"!"
"1"
"1"
"!"
)

set(S_TEST_SOURCE ${BUILDDIR}/test_identity.cpp)
init_gen_file(${S_TEST_SOURCE})

foreach(test ans IN ZIP_LISTS S_TESTS S_ANS)
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext//bqn \"${test}\""
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
  CompileParams p{
    ${cesc}
  };
  "
  )
  if("${ans}" STREQUAL "!")
    file(
      APPEND ${S_TEST_SOURCE}
      "
    REQUIRE_THROWS(vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies));
}
"
    )
  else()
    file(
      APPEND ${S_TEST_SOURCE}
      "
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
"
    )
  endif()
endforeach()
