
include(${ROOT}/cmake/GenHelpers.cmake)
message(STATUS "Generating simple tests")
set(S_TESTS
    "1+1"
    "1⌊-2"
    "-2⌊1"
    "(÷2)+(÷3)+(÷6)"
    "⊢4⊣5"
    "sq←√5,⌊9×|5-sq×sq"
    "((-3)+√(3×3)-4×2×1)÷2×2"
    "a←2,b←3,c←1⋄((-b)+√(b×b)-4×a×c)÷2×a"
    "b←1+a←1+c←1⋄((-b)+√(b×b)-4×a×c)÷2×a"
    "b←3⋄⊢d←(b×b)-4×2×1⋄((-b)+√d)÷2×2"
    "a←3,b←4,c←5⋄⊣s←(÷2)×a+b+c⋄√s×(s-a)×(s-b)×(s-c)"
    "t←2×5⋄3+(1+(4+(1+5÷t)÷t)÷t)÷t"
    "3+(1+(4+(1+5÷10)÷10)÷10)÷10"
    "√25-16"
    "¬15÷20"
    "(3∧4)-¬(¬3)∨(¬4)"
    "p←¬q←÷4⋄(q∧q)+(p∨p)"
    "105¬-3"
    "{{-3}+√{3×3}-4×2×1}÷2×2"
    "{a←1⋄{a←2}⋄a}"
)

set(S_ANS
    "2"
    "-2"
    "-1"
    "1"
    "4"
    "0"
    "-0.5"
    "-0.5"
    "-0.5"
    "-0.5"
    "6"
    "3.1415"
    "3.1415"
    "3"
    "0.25"
    "0"
    "1"
    "109"
    "-0.5"
    "1"
)

set(S_TEST_SOURCE ${BUILDDIR}/test_simple.cpp)
init_gen_file(${S_TEST_SOURCE})

foreach(test ans IN ZIP_LISTS S_TESTS S_ANS)
  execute_process(
    COMMAND ${BASH} -c
            "${BQN} ${ROOT}/test/ccxx.bqn ${ROOT}/ext//bqn \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext//cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  file(
    APPEND ${S_TEST_SOURCE}
    "
TEST_CASE(\"${test}\") {
  spdlog::critical(\"test='{}', ans='{}'\", \"${test}\", \"${ans}\");
  const auto rt = provides::get_runtime_bionly();
  const auto runtime = rt->values;
  CompileParams p{
    ${compiled_test}
  };
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
  auto n = dynamic_pointer_cast<Number>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(${ans} == doctest::Approx(n->v));
}
"
  )
endforeach()
