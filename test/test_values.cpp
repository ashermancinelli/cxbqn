#include <cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("test values", "[decode]") {
  using namespace cxbqn;
  using namespace cxbqn::value;

  SECTION("Root") {
    const auto ev = Scalar{5.0};
    const auto sut = Root{ev};
    REQUIRE(ev == Approx(decode(sut)));
  }

  SECTION("Ref") {
    f64 _ev = 5.0;
    const auto ev = Scalar{_ev};
    const auto sut = Ref(new Root{Scalar{_ev}});
    REQUIRE(ev == Approx(decode(sut)));
  }

  SECTION("Opt") {
    f64 _ev = 5.0;
    const auto ev = Scalar{_ev};
    const auto r = Ref(new Root{Scalar{_ev}});
    const auto sut = Opt{r};
    REQUIRE(ev == Approx(decode(sut)));
  }
}
