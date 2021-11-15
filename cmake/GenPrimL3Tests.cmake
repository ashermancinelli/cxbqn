if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Generating primitive l3 tests")
  set(P_TESTS
      "2≡⊑2"
      "2≡⊑⟨2⟩"
      "\\\"ab\\\"≡⊑⟨\\\"ab\\\"⟩"
      "0≡⊑↕20"
      "4≡⊑3‿2‿1⥊4⥊⊸∾5⥊0"
      "'c'≡2⊑\\\"abcd\\\""
      "'c'≡¯2⊑\\\"abcd\\\""
      "7≡7⊑↕10"
      "7≡⟨7⟩⊑↕10"
      "0≡¯10⊑↕10"
      "21≡2‿¯3⊑(10×↕3)+⌜↕4"
      "21‿12‿03≡⟨2‿¯3,1‿2,0‿¯1⟩⊑(10×↕3)+⌜↕4"
      "\\\"dfeb\\\"≡(⥊¨-⟨3,1,2,5⟩)⊑\\\"abcdef\\\""
      "\\\"abc\\\"≡⟨⟩⊑<\\\"abc\\\""
      "'a'≡⟨⟩⊑'a'"
      "⟨7,7‿7,7⟩≡⟨⟨⟩,⟨⟨⟩,⟨⟩⟩,⟨⟩⟩⊑<7"
      "⟨7,⟨7,<7⟩⟩≡⟨⟨⟩,⟨⟨⟩,<⟨⟩⟩⟩⊑7"
      "\\\"abcfab\\\"≡⥊(↕2‿3)⊑5‿5⥊\\\"abcdef\\\""
      "\\\"aedcaf\\\"≡⥊(-↕2‿3)⊑5‿5⥊\\\"abcdef\\\""
      "(<6⥊0)(⊑≡<∘⊑∘⊢)(6⥊1)⥊5"
      "¯6≡1‿0◶(2‿2⥊0‿0‿-‿0)6"
      "⟨3⟩≡⥊3"
      "(⟨⟩⊸⥊≡<)3"
      "⟨3,3,3⟩≡3⥊3"
      "⟨3,3,3⟩≡3<⊸⥊3"
      "6(⊢⌜≡∾○≢⥊⊢)○↕3"
      "(<≡↕)⟨⟩"
      "(↕∘⥊≡⥊¨∘↕)9"
      "∧´(⟨∘⟩⊸⥊≡⥊)¨ ⟨4,↕4,↕2‿4⟩"
      "1‿2‿3‿0‿1≡⥊5‿⌽⥊↑‿4⥊3‿⌊⥊1+↕4"
      "≡´⟨2‿⌽‿4,2‿3‿4⟩⥊¨<↕19"
      "¬'a'≡<'a'"
      "¬\\\"a\\\"≡≍\\\"a\\\""
      "¬⟨1,2,⟨4,4⟩,5⟩≡○(2‿2⊸⥊)⟨1,2,⟨3,4⟩,5⟩"
      "¬2‿3‿4≡2‿3"
      "¬1.001≡1.002"
      "'a'≢2"
      "2≢<2"
      "2‿3≢2‿4"
      "2‿3≢≍2‿3"
      "0≡≡'a'"
      "1≡≡↕6"
      "2≡≡↕2‿4"
      "3≡≡<<<4"
      "(1¨≡-○≡˜⟜↕¨)⟨0,⟨⟩,⟨1⟩,2,⟨3,4⟩⟩"
      "2≡≡⟨5,⟨'c',+,2⟩⟩"
      "0≡≡⊑⟨-⟩"
  )

  set(P_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim_l3.cpp")
  set(P_SETPRIMS_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim_setprims_l3.cpp")
  init_gen_file(${P_TEST_SOURCE})
  init_gen_file(${P_SETPRIMS_TEST_SOURCE})

  foreach(test ${P_TESTS})
    execute_process(
      COMMAND
        ${BASH} -c
        "${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn -i \"${test}\""
      WORKING_DIRECTORY "${CXBQN_EXT_DIR}/cbqn"
      OUTPUT_VARIABLE compiled_test
    )
    file(
      APPEND ${P_SETPRIMS_TEST_SOURCE}
      "
  TEST_CASE(\"${test}\") {
  const auto rt = provides::get_runtime_setprims_cached_annot();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${test}\");
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
  TEST_CASE(\"${test}\") {
    spdlog::critical(\"test='{}'\", \"${test}\");
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
else()
  message(
    WARNING
      "Attempted to generate primitive tests, but no BQN executable was found."
  )
endif()
