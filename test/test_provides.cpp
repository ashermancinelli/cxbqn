#include <cxbqn/cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("•Type", "") {
  SECTION("Dyad") {
    auto *t = new Type();
    auto *w = new Number(0), *x = new Number(1);
    CHECK_THROWS_AS((*t)(w, x), std::runtime_error);
    delete t;
    delete w;
    delete x;
  }
  SECTION("Array") {
    auto *t = new Type();
    auto *v = new Array({1, 2, 3});
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(0.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("Number") {
    auto *t = new Type();
    auto *v = new Number(5);
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(1.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("Character") {
    auto *t = new Type();
    auto *v = new Character('c');
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(2.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("Function") {
    auto *t = new Type();
    auto *v = new Function();
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(3.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("Md1") {
    auto *t = new Type();
    auto *v = new Md1();
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(4.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("UserMd1") {
    auto *t = new Type();
    auto *v = new UserMd1();
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(4.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("Md2") {
    auto *t = new Type();
    auto *v = new Md2();
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(5.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
  SECTION("UserMd2") {
    auto *t = new Type();
    auto *v = new UserMd2();
    auto *res = (*t)(v);
    CHECK(nullptr != dynamic_cast<Number *>(res));
    auto *n = dynamic_cast<Number *>(res);
    CHECK(5.0 == Approx(n->v));
    delete res;
    delete v;
    delete t;
  }
}

TEST_CASE("Builtins", "") {
  SECTION("w+x") {
    auto *op = new Plus();
    auto *w = new Number(2), *x = new Number(3);
    auto *ret = (*op)(w, x);
    CHECK(ret->t() == 1);
    CHECK(5.0 == Approx(dynamic_cast<Number *>(ret)->v));
    delete op;
  }
}

