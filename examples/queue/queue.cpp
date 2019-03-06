#include <iostream>
#include "queue.hpp"

using namespace std;

Sink::Sink(const char *n) : Node(n), _consumed(0)
{}

void Sink::put()
{
    _consumed ++;
}

void Sink::newRun()
{
    _consumed = 0;
}

void Sink::endRun()
{
}


Source::Source(Node* d, RandomVar* a, const char* n) : 
    Node(n),
    _at(a),
    _dest(d),
    _prodEvent(this, &Source::produce)
{
}

void Source::put() {}
    
void Source::produce(Event *e)
{
    std::cout << SIMUL.getTime() << " : Source.put()" << std::endl;
    Tick next = Tick::ceil(_at->get());
    _dest->put();
    _prodEvent.post(SIMUL.getTime() + next);
    std::cout << SIMUL.getTime() << " : Source.put(), next arrival at " << SIMUL.getTime() + next << std::endl;
}
    
void Source::newRun() 
{
    _prodEvent.post(Tick(_at->get()));
}
    
void Source::endRun()
{}



Queue::Queue(Node* d, RandomVar* st, const char* n) : 
    Node(n),
    _dest(d),
    _q(),
    _st(st),
    _servEvent(this, &Queue::serve) 
{}

void Queue::put()
{
    _q.push_back(1);
    if (_q.size() == 1)
        _servEvent.post(SIMUL.getTime() + Tick(_st->get()));
}

void Queue::serve(Event *e)
{
    _q.pop_front();
    if (_q.size() != 0) 
        _servEvent.post(SIMUL.getTime() + Tick(_st->get()));
    _dest->put();
}
    
void Queue::newRun()
{
    _q.clear();
} 
    
void Queue::endRun()
{}


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
