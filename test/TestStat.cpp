#include "catch.hpp"

#include <iostream>

#include "event.hpp"
#include "randomvar.hpp"

using namespace MetaSim;
using namespace std;

class Dummy : public StatMean {
    NormalVar nv;
public:
    Dummy(int v) : StatMean("StatMean",0), nv(v, 1) {};
    virtual void probe(Event *e) { record(nv.get()); }
    virtual void attach(Entity* e) {}
};


TEST_CASE("Test stastics", "[basestat]")
{
    Dummy *d1;
    Dummy *d2;

    int n = 5;
    int i,j;

    try {  
        BaseStat::init(n);
    
        d1 = new Dummy(7);
        d2 = new Dummy(10);
    
        for (j = 0; j < n; j++) {
            for (i = 0; i < 1000; i++) {
                d1->probe(0);
                d2->probe(0);
            }
            
            BaseStat::endRun();
      
            if (j < n-1) BaseStat::newRun();
        }
    
        BaseStat::printAll();
    } catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
} // namespace MetaSim
