if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Generating primitive l0 tests")
  set(P_TESTS
      "'a'+'c'"
      "F←-⋄f+2"
      "97-'a'"
      "@-1"
      "-'a'"
      "F←÷⋄-f"
      "2×'a'"
      "÷'b'"
      "F←√-⋄÷f"
      "⋆'π'"
      "'e'⋆'π'"
      "F←⌈⋄⌊f"
      "F←+⋄G←-⋄f≤g"
      "!0"
      "\\\"error\\\"!\\\"abc\\\""
      "√'x'"
      "'a'∧¯1"
      "F←-⋄2∨f"
      "¬'a'"
      "2¬'c'"
      "F←{𝕩}⋄0¬f"
      "F←+-⋄|f"
      "26|'A'"
      "⊑\\\"\\\""
      "⊑2‿0⥊⟨⟩"
      "+´11"
      "-´<'a'"
      "×´3‿1⥊\\\"abc\\\""
      "2‿3⊢¨4‿5‿6"
      "\\\"abcd\\\"-\\\"a\\\""
      "(↕4)×(↕3)⊢⌜↕2"
      "10⊑↕10"
      "¯11⊑↕10"
      "0.5⊑↕10"
      "'x'⊑↕10"
  )

  set(P_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim_throws.cpp")
  set(P_SETPRIMS_TEST_SOURCE
      "${PROJECT_BINARY_DIR}/test_prim_setprims_throws.cpp"
  )
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
      REQUIRE_THROWS(vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies, p.source_indices.value(), p.source_str));
      }
      "
    )
    file(
      APPEND ${P_TEST_SOURCE}
      "
      TEST_CASE(\"${test}\") {
      const auto rt = provides::get_runtime_cached();
      const auto runtime = rt->values;
      spdlog::critical(\"test='{}'\", \"${test}\");
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
