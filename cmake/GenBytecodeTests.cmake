add_custom_target(gen_bc_test ALL)

if(HAS_BQN_EXE)
  message(STATUS "Generating bytecode tests")
  set(BC_TESTS
      "5"
      "4⋄3"
      "a←5"
      "a←5⋄a↩4"
      "a←2⋄b←3⋄a"
      "a←1⋄A 4"
      "a←2⋄3 A 4"
      "{𝕩}6"
      "A←{𝕨}⋄3 A 4"
      "a‿b←7‿2⋄a"
      "4{𝔽}"
      "4{𝔽⋄𝕩}6"
      "3{𝔾}{𝕩} 1"
      "(2{𝔽}{𝕩})3"
      "3({a‿b←𝕩⋄a}{𝕨‿𝕩})4"
      "4({𝕨‿𝕩}{𝕩}{𝕨})5"
      "a‿b←(2{𝕨‿𝕩}{𝕩})5⋄a"
      "({a↩2⋄𝕩}{𝕩⋄a}{a↩3⋄𝕩})a←4"
      "a←3⋄a{𝕩}↩8⋄a"
      "a←4⋄a{𝕨⋄5}↩6"
      "a←3⋄a{𝕩⋄1}↩⋄a"
      "a‿b←2‿1⋄a‿b{𝕩‿𝕨}↩4⋄a"
      "a←1⋄{a←2}⋄a"
      "a←1⋄{a↩2}⋄a"
      "f‿g←{a←2⋄{a↩𝕩}‿{𝕩⋄a}}⋄F 6⋄G 0"
      "L←{𝕩{𝕏𝕗}}⋄{𝕏𝕤}L L L 5"
      "_l←{𝕩{𝕏𝕗} 𝔽}⋄{𝕏𝕤} {𝕩}_l 3 _l 5"
      "1{𝕨}{𝔽{𝕩𝔽𝕨}𝔾𝔽}{𝕩}0"
      "0‿(0‿{𝕩}){{a‿b←𝕩⋄t←𝕤⋄{𝕤⋄T↩{𝕤⋄{a‿b←𝕩⋄a}}}{B𝕗}0⋄(T b){a‿b←𝕩⋄𝔽b}}𝕗} 0‿(1‿(2‿(3‿(4‿{𝕩}))))"
  )
  set(BC_ANS
      5
      3
      5
      4
      2
      1
      2
      6
      3
      7
      4
      6
      1
      2
      3
      4
      2
      2
      8
      5
      1
      4
      1
      2
      6
      5
      3
      1
      2)

  set(BC_TEST_SOURCE "${PROJECT_BINARY_DIR}/test_bc.cpp")
  init_gen_file(${BC_TEST_SOURCE})

  foreach(test ans IN ZIP_LISTS BC_TESTS BC_ANS)
    execute_process(
      COMMAND
        ${BASH} -c
        "${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn \"${test}\""
      WORKING_DIRECTORY "${CXBQN_EXT_DIR}/cbqn"
      OUTPUT_VARIABLE compiled_test)
    file(
      APPEND ${BC_TEST_SOURCE}
      "
TEST_CASE(\"${test}\") {
  spdlog::critical(\"test='{}', ans='{}'\", \"${test}\", \"${ans}\");
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;
  CompileParams p{
    ${compiled_test}
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  Number *n = dynamic_cast<Number *>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
")
  endforeach()
else()
  message(
    WARNING
      "Attempted to generate bytecode tests, but no BQN executable was found.")
endif()
