#include "myentity.hpp"

#include "catch.hpp"

using namespace std;

TEST_CASE("TestEventOrder", "testPost")
{ 
    MyEntity me("Pippo");
    SIMUL.run(12);
    REQUIRE(me.isAFirst());
    REQUIRE(me.getCounter() == 2);
}
