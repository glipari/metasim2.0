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

    AvgQueueSizeStat avgSizeStat(que, "avg_queue_size");
    attach_stat(avgSizeStat, source._prodEvent);

    BaseStat::setTransitory(20);
  
    SIMUL.dbg.setStream("log.txt");
    SIMUL.dbg.enable("All");

    Tick t;
    SIMUL.initRuns();
    SIMUL.initSingleRun();
    while ((t = SIMUL.sim_step()) < 200) {
        cout << "Time: " << t << endl;
        getchar();
    }

    cout << "The average queue length is " 
         << avgSizeStat.getMean() << endl;
    cout << "with a 95% confidence interval of " 
         << avgSizeStat.getConfInterval(BaseStat::C95) << endl;
}//end main
