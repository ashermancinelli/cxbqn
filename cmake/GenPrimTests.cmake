if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Generating primitive tests")
  set(P_TESTS
      "0≡¯2+2"
      "1e4≡5e3+5e3"
      "'c'≡'a'+2"
      "'a'≡¯2+'c'"
      "¯∞≡1e6-∞"
      "4≡-¯4"
      "¯∞≡-∞"
      "∞≡-¯∞"
      "4≡9-5"
      "@≡'a'-97"
      "3≡'d'-'a'"
      "'Q'≡'q'+'A'-'a'"
      "4≡÷0.25"
      "∞≡÷0"
      "0≡÷∞"
      "1≡⋆0"
      "¯1≡¯1⋆5"
      "1≡¯1⋆¯6"
      "3≡⌊3.9"
      "¯4≡⌊¯3.9"
      "∞≡⌊∞"
      "¯∞≡⌊¯∞"
      "¯1e30≡⌊¯1e30"
      "1≡1=1"
      "0≡¯1=∞"
      "1≡'a'='a'"
      "0≡'a'='A'"
      "1≡{F←+⋄f=f}"
      "1≡{a‿b←⟨+´,+´⟩⋄a=b}"
      "0≡{_op←{𝕗}⋄op='o'}"
      "0≡{F←{𝕩}⋄G←{𝕩}⋄f=g}"
      "1≡{F←{𝕩}⋄f=f}"
      "1≡1≤1"
      "1≡¯∞≤¯1e3"
      "0≡∞≤¯∞"
      "1≡∞≤@"
      "0≡'z'≤¯0.5"
      "1≡'a'≤'a'"
      "0≡'c'≤'a'"
      "⟨⟩≡≢<2"
      "⟨3⟩≡≢\\\"abc\\\""
      "⟨2,3⟩≡≢>\\\"abc\\\"‿\\\"fed\\\""
      "⟨2,3,4,5⟩≡≢2‿3‿4‿5⥊↕120"
      "⟨6⟩≡≢⥊>\\\"abc\\\"‿\\\"fed\\\""
      "\\\"abc\\\"≡0⊑\\\"abc\\\"‿\\\"de\\\""
      "\\\"de\\\"≡1⊑\\\"abc\\\"‿\\\"de\\\""
      "⟨⟩≡↕0"
      "⟨0⟩≡↕1"
      "⟨0,1,2,3,4,5,6⟩≡↕7"
      "1≡!1"
      "1≡'e'!1"
  )
  set(P_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim.cpp")
  init_gen_file(${P_TEST_SOURCE})

  foreach(test ${P_TESTS})
    execute_process(
      COMMAND
        ${BASH} -c
        "${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn \"${test}\""
      WORKING_DIRECTORY "${CXBQN_EXT_DIR}/cbqn"
      OUTPUT_VARIABLE compiled_test
    )
    file(
      APPEND ${P_TEST_SOURCE}
      "
TEST_CASE(\"${test}\") {
  spdlog::critical(\"test='{}'\", \"${test}\");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{ ${compiled_test} };
"
    )

    file(
      APPEND ${P_TEST_SOURCE}
      "
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
else()
  message(
    WARNING
      "Attempted to generate primitive tests, but no BQN executable was found."
  )
endif()
