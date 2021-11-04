add_custom_target(gen_simple_test ALL)

if(HAS_BQN_EXE)
  find_package(UnixCommands REQUIRED)
  message(STATUS "Dynamically generating simple tests")
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
      "{a←1⋄{a←2}⋄a}")

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
      "1")

  set(GEN_S_TEST_FILE "${PROJECT_BINARY_DIR}/gen-simple-test.sh")
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/simple_tests)
  file(REMOVE ${GEN_S_TEST_FILE})
  file(WRITE ${GEN_S_TEST_FILE} "cd ${CXBQN_EXT_DIR}/cbqn\n")

  set(i 0)
  foreach(S_TEST ${S_TESTS})
    list(GET S_ANS ${i} ans)
    file(
      APPEND ${GEN_S_TEST_FILE}
      "echo -e '/* ${S_TEST} */' > ${PROJECT_BINARY_DIR}/include/simple_tests/t${i}.hpp
      echo -e '/* ${S_TEST} */' > ${PROJECT_BINARY_DIR}/include/simple_tests/a${i}.hpp
${BQN_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/ccxx.bqn ${CXBQN_EXT_DIR}/bqn '${S_TEST}' >> ${PROJECT_BINARY_DIR}/include/simple_tests/t${i}.hpp
      echo -e '${ans}' > ${PROJECT_BINARY_DIR}/include/simple_tests/a${i}.hpp\n"
    )
    math(EXPR i "${i} + 1")
  endforeach()

  add_custom_command(
    COMMENT "Generating simple tests"
    DEPENDS ccxx.bqn
    COMMAND bash ${GEN_S_TEST_FILE}
    OUTPUT ${PROJECT_BINARY_DIR}/include/simple_tests/t0.hpp)
  add_custom_target(
    do_gen_simple_test DEPENDS ${PROJECT_BINARY_DIR}/include/simple_tests/t0.hpp
                               ccxx.bqn)
else()
  add_custom_target(
    do_gen_simple_test
    COMMAND
      ${CMAKE_COMMAND} -E echo
      "simple tests could not be generated becuase no BQN executable could be found."
  )
endif()

add_dependencies(gen_simple_test do_gen_simple_test)
