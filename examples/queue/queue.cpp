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
    DBGENTER(QueueDbgLevel);

    Tick next = Tick::round(_at->get());
    _dest->put();
    _prodEvent.post(SIMUL.getTime() + next);

    DBGPRINT_2("Next arrival at ", (SIMUL.getTime() + next));
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
    DBGENTER(QueueDbgLevel);
    
    _q.push_back(1);

    DBGPRINT_2("Queue size is now ", _q.size());
    
    if (_q.size() == 1) {
        Tick completion = SIMUL.getTime() + Tick(_st->get());
        _servEvent.post(completion);
        DBGPRINT_2("Completion at ", completion);
    }
}

void Queue::serve(Event *e)
{
    DBGENTER(QueueDbgLevel);
    
    _q.pop_front();

    DBGPRINT_2("Queue size: ", _q.size()); 

    if (_q.size() != 0) {
        Tick next = SIMUL.getTime() + Tick(_st->get());
        _servEvent.post(next);
        DBGPRINT_2("Now serving next packet, completion at ", next); 
    }
    _dest->put();
}
    
void Queue::newRun()
{
    _q.clear();
} 
    
void Queue::endRun()
{}


