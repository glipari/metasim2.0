#include <iostream>
#include <queue.hpp>

using namespace std;

int main() 
{
    double lambda, mu;

    lambda = 0.05;
    mu = 0.075;

    ExponentialVar st(lambda);
    ExponentialVar at(mu);
        
    cout << "service : " << st.get() << endl;
    cout << "interarr: " << at.get() << endl;
        
    Sink sink("sink");
    Queue que(&sink, &st, "M/M/1 queue");
    Source source(&que, &at, "source");
  
    SIMUL.dbg.enable(QueueDbgLevel);

    Tick t;
    SIMUL.initRuns();
    SIMUL.initSingleRun();
    while ((t = SIMUL.sim_step()) < 200) {
        cout << "Time: " << t << endl;
        getchar();
    }
}//end main
