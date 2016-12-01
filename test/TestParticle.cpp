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

    // void attach(MyEntity &ent) {
    //     //new Particle<GEvent<MyEntity>, MyStat>(ent.eventA, *this);
    //     attach_stat(*this, ent.eventA);
    // }
};

TEST_CASE("Test Particle interface", "[statistics]")
{
    MyEntity me("Pippo");
    MyStat s;
    attach_stat(s, me.eventA);
    
    SIMUL.run(12);

    REQUIRE(s.getValue() == 4);
}

