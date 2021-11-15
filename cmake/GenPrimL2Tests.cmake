if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Generating primitive l2 tests")
  set(P_TESTS
  "⟨⟩≡⟨⟩∾\\\"\\\""
  "\\\"a\\\"≡⟨⟩∾\\\"a\\\""
  "\\\"a\\\"≡\\\"a\\\"∾⟨⟩"
  "\\\"aBCD\\\"≡\\\"a\\\"∾\\\"BCD\\\""
  "((+⌜˜≠¨)≡(≠¨∾⌜˜))\\\"\\\"‿⟨2,3⟩‿\\\"abcde\\\""
  "(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)3‿4"
  "(⥊⟜(↕×´)≡(×⟜4)⊸(+⌜)○↕´)0‿4"
  "(3‿2‿0⥊\\\"\\\")≡(3‿2⥊↕6)+⌜\\\"\\\""
  "(<-2)≡-¨2"
  "(<<2)≡<¨2"
  "⟨1,⟨3,2,2‿2⥊⟨1,0,2,0⟩⟩,⟨5,4⟩⟩≡-⟨-1,⟨-3,-2,-¨2‿2⥊⟨1,0,2,0⟩⟩,⟨-5,-4⟩⟩"
  "3(+¨≡+⌜)↕6"
  "3‿4‿5‿6‿6≡{𝕊⍟(×≡)⊸∾⟜⥊´𝕩}⟨2,1⟩+⟨⟨⟨⟨1,2⟩,3⟩,4⟩,5⟩"
  "3‿2≡≢(↕3)(⊣×⊢⌜)↕2"
  "(<-4)≡-<4"
  "(<2)≡1+<1"
  "(=¨⟜(⥊⟜(↕×´)3‿4)≡(↕4)=⌜˜4|⊢)1‿6‿8"
  "0‿1≡+‿-=⊑⟨-⟩"
  )

  set(P_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim_l2.cpp")
  set(P_SETPRIMS_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_prim_setprims_l2.cpp")
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
