
include(${ROOT}/cmake/GenHelpers.cmake)

message(STATUS "Generating primitive l4 tests")
set(P_TESTS
    "\\\"a\\\"â¡â'a'"
    "({â¨ð©â©}â¡â)'a'â¿2"
    "\\\"abc\\\"â¿1â¡\\\"abc\\\"â1"
    "âÂ´â¸â¡\\\"ab\\\""
    "â§Â´â¡â>Â¨â¨1,<'a',<â,â5,5â¿3â¥2â©"
    "2â¿3â¿2â¡â¢>â2â¿3"
    "2â¿3â¡>â¨<2,3â©"
    "((4â¥2)â¸â¥â¡(>2â¿2â¥Â·<2â¿2â¥â¢))\\\"abcd\\\""
    "(â¢â¡>â<)5â¿3â¥â15"
    "(â¢â¡(><Â¨))5â¿3â¥â15"
    "(â¥â¡â)'a'"
    "(â¥â¡â)<'a'"
    "(1â¿2â¸â¥â¡â)\\\"ab\\\""
    "1â¿2â¡1â2"
    "2â¿1(ââ¡2â¿2â¥â¾)4â¿3"
    "(ââ<â¡âË)'a'"
    "(âËËâ¥Ë1â¿5â¿9)â¡â½â2â¸+â¥â(âÃÂ´)3â¿2â¿1"
    "(<0)â¡â¡Ë0"
    "(<1)â¡â¡Ë<0"
    "(2â¥<<\\\"ab\\\") â¡ âËË<\\\"ab\\\""
    "(3â¥0) â¡ {-}=Ëâ3"
    "(â4)(Ãââ¡Ãâ0â¿2)â5"
    "(â4)(âËâËâ¡ââââ¿Â¯4)â5"
    "(â¨2â©â¸â¾â(2â¿2â¥0â¿1â¿1â¿1)2â¿3)â¡â¢Â¨ââ(ââ=)âËâ¨â3,2â¿3â¥â6â©"
    "(2=âââ3)â¡(2â¿4â¥\\\"abc\\\")â¡â1(2â¿3â¿4â¥\\\"abc\\\")"
    "â¨0,0â©â¡(2â¿4â¥\\\"abc\\\")â¡âÂ¯1(2â¿3â¿4â¥\\\"abc\\\")"
    "(-â¡-âÂ¯1)5"
    "â¨5,â¨15,1â©â©â¡+Â´â1â¨â¨3,2â©,â¨â¨4,5,6â©,â¨1â©â©â©"
    "5â¿6â¿15â¡â¾Â´+Â´â1â¨â¨0,1â©,â¨â¨â©â©â©â¥â¸â¾âÂ¯2â¿1â¨â¨2,3â©,â¨4,5,6â©â©"
    "(5â¥1)â¡(â5)=â=â0{â}"
    "4â¡2+âÂ¯1 6"
    "(2Ãâ7)â¡2+â(Â¯3+â7)6"
    "(3ââ5)â¡{iâ0ârâ{i+â©1â1+ð©}â(â4)ð©ârâ¾i}0"
    "(+âËâ¡Â·>1+ââ¢â¢)â5"
    "0â¿1â¿3â¿6â¿10â¡+\\`â5"
    "(-0â¿1â¿3â¿6â¿10)â¡-\\`â5"
    "((0â¾Â¨â3)â3â¥0)â¡â¡\\`â2â¿3"
    "â¨â©â¡Ã\\`â¨â©"
    "â¡â(!â0\\`)3â¿0â¿2â¥\\\"\\\""
    "2â¿3â¿5â¿8â¿12â¡2+\\`â5"
    "(2â1â¿2â¿6Ãâ0â¿2)â¡3â¿4â\\`3+âââ2"
)

set(P_TEST_SOURCE "${BUILDDIR}/test_prim_l4.cpp")
set(P_SETPRIMS_TEST_SOURCE "${BUILDDIR}/test_prim_setprims_l4.cpp")
init_gen_file(${P_TEST_SOURCE})
init_gen_file(${P_SETPRIMS_TEST_SOURCE})

foreach(test ${P_TESTS})
  execute_process(
    COMMAND
      ${BASH} -c
      "${BQN} ${ROOT}/test/ccx.bqn ${ROOT}/ext//bqn \"${test}\""
    WORKING_DIRECTORY "${ROOT}/ext//cbqn"
    OUTPUT_VARIABLE compiled_test
  )
  string(REPLACE "\\`" "`" noesc "${test}")
  file(
    APPEND ${P_SETPRIMS_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
  const auto rt = provides::get_runtime_setprims_cached();
  const auto runtime = rt->values;
  spdlog::critical(\"test='{}'\", \"${noesc}\");
  auto cu = ${compiled_test};
  auto ret = vm::run(cu);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dyncast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
  file(
    APPEND ${P_TEST_SOURCE}
    "
  TEST_CASE(\"${noesc}\") {
    spdlog::critical(\"test='{}'\", \"${noesc}\");
  const auto rt = provides::get_runtime_cached();
  const auto runtime = rt->values;
    auto cu = ${compiled_test};
    auto ret = vm::run(cu);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    auto n = dyncast<Number>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1 == doctest::Approx(n->v));
  }
"
  )
endforeach()
