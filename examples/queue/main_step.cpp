#include <iostream>
#include <queue.hpp>

using namespace std;

int main() 
{
    double mu = 1.0 / 10;

    DetVar at( {15.0} );
    ExponentialVar st(mu);

    vector<double> va;
    vector<double> vs;
    
    for(int i=0; i<10; i++) {
        va.push_back(at.get());
        vs.push_back(st.get());
    }
    
    cout << "Arrivals" << endl;
    for (auto x : va) cout << x << ", ";
    cout << endl;
    cout << "Services" << endl;
    for (auto x : vs) cout << x << ", ";
    cout << endl;

    /*----------------------------------------*/
    
    Sink sink("sink");
    Queue que(&sink, &st, "M/M/1 queue");
    Source source(&que, &at, "source");
  
    SIMUL.dbg.enable(QueueDbgLevel);

    Tick t;
    SIMUL.initRuns();
    SIMUL.initSingleRun();
    while ((t = SIMUL.sim_step()) < 200) {
        getchar();
    }
}//end main
