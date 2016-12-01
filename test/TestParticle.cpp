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

    void attach(MyEntity &ent) {
        new Particle<GEvent<MyEntity>, MyStat>(&ent.eventA, this);
    }
};

TEST_CASE("Test Particle interface", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    s.attach(me);
    
    SIMUL.run(12);

    REQUIRE(s.getValue() == 4);
}

