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


