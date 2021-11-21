include(${ROOT}/cmake/GenHelpers.cmake)
message(STATUS "Generating primitive l1 tests")
set(P_TESTS
    "3≡4>◶+‿-1"
    "3≡4⊢◶+‿-1"
    "3≡4 1◶+‿-1"
    "5≡4<◶+‿-1"
    "5≡4 0◶+‿-1"
    "1≡-⊘0 ¯1"
    "1≡¯1-⊘+2"
    "\\\"abc\\\"≡⊢\\\"abc\\\""
    "\\\"\\\"≡3⊢\\\"\\\""
    "⟨⟩≡⊣⟨⟩"
    "\\\"ab\\\"≡\\\"ab\\\"⊣⟨⟩"
    "4≡+˜2"
    "3≡1-˜4"
    "1≡-∘×¯6"
    "¯6≡2-∘×3"
    "1≡-○×¯7"
    "2≡5-○×¯7"
    "¯20≡1⊸-⊸×5"
    "(0‿2+⌜0‿1)≡(>⟨\\\"ab\\\",\\\"cd\\\"⟩)≢⊸⥊↕4"
    "20≡×⟜(-⟜1)5"
    "4≡5+⟜×¯3"
    "7≡5+⟜2 ¯3"
    "2≡√4"
    "3≡3√27"
    "6≡2∧3"
    "0≡¯2∧0"
    "0.75≡∨˜0.5"
    "1.75≡2∨0.25"
    "0≡¬1"
    "1≡¬0"
    "2≡¬¯1"
    "0≡3¬4"
    "2≡4¬3"
    "4≡5¬2"
    "5≡'g'¬'c'"
    "'b'≡'c'¬2"
    "0≡|0"
    "5≡|¯5"
    "6≡|6"
    "∞≡|¯∞"
    "2≡3|8"
    "2≡3|¯7"
    "¯1≡¯3|8"
    "\\\"a\\\"≡⥊<'a'"
    "\\\"abcd\\\"≡⊑<\\\"abcd\\\""
    "⟨⟩≡≢<⟨2,⟨3,4⟩⟩"
    "0≡4<2"
    "0≡5>5"
    "0≡3≥4"
    "0≡≠\\\"\\\""
    "1≡≠\\\"a\\\""
    "1≡≠'a'"
    "2≡≠\\\"ab\\\""
    "25≡≠↕25"
    "1≡×5"
    "¯1≡×¯2.5"
    "3≡3⌊4"
    "¯3≡¯3⌊∞"
    "4≡3⌈4"
    "1≡1⌈¯1"
    "5≡⌈4.01"
    "⟨⟩≡≢'a'"
    "⟨⟩≡≢0"
    "⟨0⟩‿⟨1⟩‿⟨2⟩≡⥊¨↕3"
    "(↕6)≡⟜(≠¨)○(2‿3⊸⥊)⟨⟩‿\\\"a\\\"‿\\\"ab\\\"‿\\\"abc\\\"‿\\\"abcd\\\"‿\\\"abcde\\\"‿\\\"abcdef\\\""
    "≡⟜(≠¨)4‿0‿2⥊↕0"
    "6≡+´↕4"
    "(⊑≡⊣´)\\\"a\\\"‿2‿(3‿\\\"d\\\")"
    "0(⊑≡⊣´)\\\"a\\\"‿2‿(3‿\\\"d\\\")"
    "(2⊸⊑≡⊢´)\\\"a\\\"‿2‿(3‿\\\"d\\\")"
    "2(⊣≡⊢´)\\\"a\\\"‿2‿(3‿\\\"d\\\")"
    "7‿10≡+¨´⟨⟨2,3⟩,⟨5,7⟩⟩"
)

set(P_TEST_SOURCE "${BUILDDIR}/test_prim_l1.cpp")
set(P_SETPRIMS_TEST_SOURCE "${BUILDDIR}/test_prim_setprims_l1.cpp")
init_gen_file(${P_TEST_SOURCE})
init_gen_file(${P_SETPRIMS_TEST_SOURCE})

foreach(test ${P_TESTS})
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext/bqn -i \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext/cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  file(
    APPEND ${P_SETPRIMS_TEST_SOURCE}
    "
    TEST_CASE(\"${test}\") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${test}\");
  CompileParams p( ${compiled_test} );
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies, p.source_indices.value(), p.source_str);
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
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
    spdlog::critical(\"test='{}'\", \"${test}\");
    CompileParams p{ ${compiled_test} };
    auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dynamic_pointer_cast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
