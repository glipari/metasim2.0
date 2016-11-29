#include <tick.hpp>
#include <cstdint>
#include <climits>

#include "catch.hpp"

using namespace MetaSim;

TEST_CASE("TestTick", "testBoolean")
{
    Tick a;
    Tick b(5);
    Tick c(5);

    REQUIRE(a < b);
    REQUIRE(b == c);
    REQUIRE(c >= a);
}

TEST_CASE("TestTick2", "testOperations")
{
    Tick a;
    Tick b(100);
    Tick c("4ns");
    Tick d(".4us");

    REQUIRE((100*c) == d);
    REQUIRE((a+b) == 100);
    REQUIRE((b/100) == 1);
    REQUIRE(a++ == 0);
    REQUIRE(++a == 2);
    REQUIRE((d/400) == 1);
}

TEST_CASE("TestTick3", "testOverflow")
{
    Tick sc_m = SCHAR_MIN;
    Tick sc_M = SCHAR_MAX;
    REQUIRE(sc_m == SCHAR_MIN);
    REQUIRE(sc_M == SCHAR_MAX);

    Tick ss_m = SHRT_MIN;
    Tick ss_M = SHRT_MAX;
    REQUIRE(ss_m == SHRT_MIN);
    REQUIRE(ss_M == SHRT_MAX);

    Tick i_m = INT_MIN;
    Tick i_M = INT_MAX;
    REQUIRE(i_m == INT_MIN);
    REQUIRE(i_M == INT_MAX);
	
    Tick ll_m = static_cast<int64_t>(LLONG_MIN);
    Tick ll_M = static_cast<int64_t>(LLONG_MAX);
    REQUIRE(ll_m == static_cast<int64_t>(LLONG_MIN));
    REQUIRE(ll_M == static_cast<int64_t>(LLONG_MAX));
}



