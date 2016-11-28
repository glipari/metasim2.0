#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <randomvar.hpp>
#include <regvar.hpp>
#include "catch.hpp"

using namespace std;

TEST_CASE("Test random vars", "[random, factory]")
{
    MetaSim::RandomVar *p = MetaSim::RandomVar::parsevar("delta(5)");

    REQUIRE(p->get() == 5);
    REQUIRE(p->getMaximum() == 5);
    REQUIRE(p->getMinimum() == 5);

    delete p;
}
