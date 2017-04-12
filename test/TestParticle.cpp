#include <myentity.hpp>
#include <basestat.hpp>
#include <iostream>
#include "catch.hpp"

using namespace std;
using namespace MetaSim;

class MyStat : public StatCount {
public:
    void probe(MetaSim::GEvent<MyEntity> &e) {
        record(1);
    }
};

TEST_CASE("Test Particle interface", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);
    
    SIMUL.run(2);

    REQUIRE(s.getValue() == 0);
    REQUIRE(s.getLastValue() == 0);
}

TEST_CASE("Test Particle copying", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);

    // the statistic is duplicated when you copy the entity
    MyEntity you("Pluto");
    
    SIMUL.run(12);

    REQUIRE(s.getValue() == 8);
}

TEST_CASE("Test Particle getLastValue()", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);
    attach_stat(s, me.eventB);
    
    SIMUL.run(25);  // 

    REQUIRE(s.getValue() == 4);
    REQUIRE(s.getLastValue() == 4);
}
