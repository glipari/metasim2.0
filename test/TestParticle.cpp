#include <iostream>
#include "catch.hpp"

#include <basestat.hpp>
#include <myentity.hpp>

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
    
    SIMUL.run(12);

    REQUIRE(s.getValue() == 4); // 0, 5, 10, 15
                                /* the last one is executed because it is the first after the sim limit */
                                /* maybe we should change this behaviour */

    /* check that last value is correctly updated */ 
    REQUIRE(s.getLastValue() == 4);
}

TEST_CASE("Test Particle copying", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);

    // the particle is duplicated when you copy the entity
    MyEntity you(me);
    
    SIMUL.run(12);

    // 0, 0, 5, 5, 10, 10, 15
    REQUIRE(s.getValue() == 7);
}

TEST_CASE("Test Particle getLastValue()", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);
    attach_stat(s, me.eventB);
    
    SIMUL.run(25); 

    // 0, 5, 10, 15, 20, 25 for eventA
    // 0, 10, 20 for eventB
    REQUIRE(s.getValue() == 9);
    REQUIRE(s.getLastValue() == 9);
}
