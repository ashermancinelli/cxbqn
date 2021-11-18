include(${ROOT}/cmake/GenHelpers.cmake)
message(STATUS "Generating bytecode tests...")
set(BC_TESTS
    "5                     #  0 PUSH,  7 RETN"
    "4⋄3                   #  6 POPS"
    "a←5                   # 33 VARM, 48 SETN"
    "a←5⋄a↩4               # 49 SETU"
    "a←2⋄b←3⋄a             # 32 VARO"
    "a←1⋄A 4               # 16 FN1C"
    "a←2⋄3 A 4             # 17 FN2C"
    "{𝕩}6                  #  1 DFND"
    "A←{𝕨}⋄3 A 4           #    dyadic block function"
    "a‿b←7‿2⋄a             # 11 ARRO, 12 ARRM"
    "0{𝕨𝕏1}2               # 19 FN2O (doesn't test call type)"
    "{({𝕨}𝕨)𝕏𝕩}5           # 18 FN1O not called"
    "{𝕩{a‿b←𝕨}𝕨,𝕩}8        # 19 FN2O not called"
    "4{𝔽}                  # 26 MD1C"
    "4{𝔽⋄𝕩}6               #    deferred modifier"
    "3{𝔾}{𝕩} 1             # 27 MD2C"
    "(2{𝔽}{𝕩})3            # 20 TR2D"
    "3({a‿b←𝕩⋄a}{𝕨‿𝕩})4    #    dyadic 2-train"
    "4({𝕨‿𝕩}{𝕩}{𝕨})5       # 21 TR3D"
    "a‿b←(2{𝕨‿𝕩}{𝕩})5⋄a    #    monadic, data in left branch"
    "({a↩2⋄𝕩}{𝕩⋄a}{a↩3⋄𝕩})a←4 # ordering"
    "a←3⋄a{𝕩}↩8⋄a          # 50 SETM"
    "a←4⋄a{𝕨⋄5}↩6          #    returns new value"
    "a←3⋄a{𝕩⋄1}↩⋄a         # 51 SETC"
    "a‿b←2‿1⋄a‿b{𝕩‿𝕨}↩4⋄a  #    lists"
    "     {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type"
    "    3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7  # 19 FN2O call type"
    "{𝕏0} {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type"
    "{𝕏0}3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7  # 23 TR3O call type"
    "a←1⋄{a←2}⋄a"
    "a←1⋄{a↩2}⋄a"
    "f‿g←{a←2⋄{a↩𝕩}‿{𝕩⋄a}}⋄F 6⋄G 0"
    "L←{𝕩{𝕏𝕗}}⋄{𝕏𝕤}L L L 5"
    "_l←{𝕩{𝕏𝕗} 𝔽}⋄{𝕏𝕤} {𝕩}_l 3 _l 5"
    "1{𝕨}{𝔽{𝕩𝔽𝕨}𝔾𝔽}{𝕩}0    # 0≠1 via Church booleans"
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
    2
    5
    8
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
    7
    3
    7
    3
    1
    2
    6
    5
    3
    1
    2
)
set(BC_TEST_SOURCE "${BUILDDIR}/test_bc.cpp")
init_gen_file(${BC_TEST_SOURCE})

foreach(test ans IN ZIP_LISTS BC_TESTS BC_ANS)
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext/bqn \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext/cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  file(
    APPEND ${BC_TEST_SOURCE}
    "
TEST_CASE(\"${test}\") {
  spdlog::critical(\"test='{}', ans='{}'\", \"${test}\", \"${ans}\");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
    ${compiled_test}
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
"
  )
endforeach()
