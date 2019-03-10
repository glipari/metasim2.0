#include <deque>

#include <metasim.hpp>
#include <particle.hpp>

using namespace MetaSim;

const std::string QueueDbgLevel("Queue DBG");

/**
 *  The Node class represents a generic node in the system. A node can
 *  be a sink, a source, or a queue. It has a pure virtual method,
 *  <i>put()</i> that inserts a packet in the node. */
class Node : public Entity {
public:
    Node(const char *n) : Entity(n) {}

    virtual void put() = 0;
    
    virtual void newRun() {}
    virtual void endRun() {}
    virtual void print() {}
};


/**
 * This class models a sink. The put method does nothing else than
 * recording how many packet have been consumed since the beginning.  */
class Sink : public Node {
    int _consumed;
public:
    Sink(const char *n);
    virtual void put(); 
    virtual void newRun();
    virtual void endRun();
};


/**
 * This class models a source. The put method does nothing. The source
 * produces packets that will be inserted into the destination node. 
*/
class Source : public Node {
    RandomVar* _at;
    Node* _dest;
public:   
    GEvent<Source> _prodEvent;
    
    Source(Node* d, RandomVar* a, const char* n);
    
    void put();
    void produce(Event *);
    void newRun();
    void endRun();
};

/**
 * This class implements a generic queue with one server, with
 * randomly distributed service times. The service time is independent
 * form the packet. After servicing a packet, the queue node will
 * send the packet to the destination node, that can be another queue
 * or a sink. In this way we can specify simple networks of queues. */
class Queue: public Node {
    /// The destination node 
    Node* _dest;
    
    /** 
     *  The internal queue representation. See a description of the stl
     *  for more details on the deque (double ended queue) data
     *  structure.  This is a queue of integers: in this simple example,
     *  every packet has lenght 1. However, it is quite easy to define
     *  a sligtly different model in which the service time depends on
     *  the packet length...*/
    std::deque<int> _q;
    
    /**
     * The service time random variable. It is possible to define a
     * general distribution! */
    RandomVar *_st;
    
public:
    /**
     *  This class models an event of packed served. When a packet is
     *  ready to be served, an event of this type is <i>posted</i> in the
     *  future. When that time comes, the <i>doit()</i> method is
     *  invoked. */
    
    /// The event of served packet.
    GEvent<Queue> _servEvent;
    
    /**
     * Constructor for a queue. 
     * @param d   pointer to the destination node
     * @param st  service time random variable
     * @param n   a simbolyc name for the queue.
     */
    Queue(Node* d, RandomVar* st, const char* n);
    
    void put();
    void serve(Event *e);
    inline int getSize() { return (int) _q.size(); }
    void newRun();
    void endRun();
}; 


/* ----------------------------------------------------------------------*/

/**
   This statistics measures the average lenght of the queue. 
 */
class AvgQueueSizeStat : public StatMean {
    Queue &_queue;
public:
    AvgQueueSizeStat(Queue &q, const char *n) :
        StatMean(n),
        _queue(q) {}
    
    void probe(Event &e) {
        record(_queue.getSize() - 1);
    }
};
