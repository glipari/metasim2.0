#include <vector>
#include <simul.hpp>
#include <randomvar.hpp>

const char* const _MARKOV_DBG_LEV = "Markov";

using namespace MetaSim;

class State;

// it represents a link between two states
class Link {
    MetaSim::ExponentialVar a;
    MetaSim::Tick last_number;
    State *dest;

public:  
    Link(double avg, State *p) : a(avg) {dest = p;}
    void new_number() {last_number = MetaSim::Tick(a.get());}
    MetaSim::Tick get_number() {return last_number;}
    State *get_dest() {return dest;}
};


// it represents a jump event between two states. Each state has its own 
// jump event
class JumpEvent : public MetaSim::Event {
    // _sender points to the state which owns the event. This
    // event arises when the owner state is the current active
    // state and a new state must become active (the next active
    // state is *_receiver)
    State *_sender;
    State *_receiver;
public:
    JumpEvent(State *s) {_sender = s;}
    virtual void doit();     
    void setReceiver(State *s) {_receiver = s;}
    State *getReceiver() {return _receiver;}
    State *getSender() {return _sender;}
};

/**
 *  The State class represents a generic state of the markov chain. */
class State : public MetaSim::Entity {
    bool _running;
    MetaSim::Tick _lastArrival;
    bool _initialState;
    std::vector<Link> _links;

public:  
    JumpEvent _event;

    State(const char *n, bool ini = false) : 
        Entity(n),
        _running(false),
        _lastArrival(0),
        _initialState(ini),
        _links(),
        _event(this)
        {
        }

    void run(); 

    void set_running() { _running = true; }
    void clear_running() { _running = false; }

    MetaSim::Tick get_last_arrival() const { return _lastArrival; } 

    void put_link(double avg, State *p)
        {
            Link temp(avg, p);
            _links.push_back(temp);
        }
        
    virtual void newRun();
    virtual void endRun() {}
    virtual void print() {}
};


// This statistic class is able to compute in the average the interval of
// time spent in a certain state during a simulation interval of time.
class AvgTimeStateStat : public MetaSim::StatCount {
public:
    AvgTimeStateStat(const char *n) : MetaSim::StatCount(n) {}
    void probe(JumpEvent &ev)
        {
            State *sender = ev.getSender();
            record(double(SIMUL.getTime() - sender->get_last_arrival()));
        }
};
