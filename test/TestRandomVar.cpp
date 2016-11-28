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

    SECTION ("Testing delta") {
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(5)");
        
        REQUIRE(p->get() == 5);
        REQUIRE(p->getMaximum() == 5);
        REQUIRE(p->getMinimum() == 5);
    }
    SECTION ("Testing exp") {
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exponential(5)");
        
        double v = q->get();
        REQUIRE (v <= 59);
        REQUIRE (v >= 58);
        REQUIRE (q->getMinimum() == 0);
        REQUIRE_THROWS(q->getMaximum());
    }

    SECTION ("Testing a vector of random vars") {
        vector<unique_ptr<MetaSim::RandomVar> > v_obj;
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(2)");
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(std::move(p));
        v_obj.push_back(std::move(q));

        REQUIRE(v_obj[0]->get() == 2);
        REQUIRE_THROWS(v_obj[1]->getMaximum());
    }
    SECTION ("Testing a vector of random vars with shared_ptr<>") {
        vector<shared_ptr<MetaSim::RandomVar> > v_obj;
        unique_ptr<MetaSim::RandomVar> p = MetaSim::RandomVar::parsevar("delta(2)");
        unique_ptr<MetaSim::RandomVar> q = MetaSim::RandomVar::parsevar("exp(5)");

        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(p)));
        v_obj.push_back(shared_ptr<MetaSim::RandomVar>(std::move(q)));

        vector<shared_ptr<MetaSim::RandomVar> > v2_obj(v_obj);
        REQUIRE(v2_obj[0]->get() == 2);
        REQUIRE_THROWS(v2_obj[1]->getMaximum());
    }   
}

