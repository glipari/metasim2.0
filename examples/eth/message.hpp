#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <metasim.hpp>

#define _MESSAGE_DBG "EthernetLink"

class Node;
class NetInterface;

class Message {
    int _len;
    
    //  Started from node and arrived at the link 
    MetaSim::Tick _start_time;
    // Started from interface anr arrived at the link 
    MetaSim::Tick _trans_time;
    // end of transmission, arrived at destination interface 
    MetaSim::Tick _arr_time;
    
    // destination node
    Node *_dst;
    // source node
    Node *_src;
    
    // // destination interface (obtained from the dst node)
    // NetInterface *_dst_net_interf;
    // // source interface (obtained from the src node)
    // NetInterface *_src_net_interf;

public:

    /** Constructor
      
        @param l lenght of the message 
        @param src address of the source node
        @param dst address of the destination node
    */
    Message(int l, Node *src, Node *dest);

    // Copy constructor is automatically defined by the compiler
    
    // Set the starting time of the message
    void setStartTime(MetaSim::Tick t);
    MetaSim::Tick getStartTime();

    // Transmission time
    void setTransTime(MetaSim::Tick t);
    MetaSim::Tick getTransTime();

    // Arrival time
    void setArrTime(MetaSim::Tick t);
    MetaSim::Tick getArrTime();

    // Message lenght
    int getLength();

    // void setSourceInterface(NetInterface *n);
    // void setDestInterface(NetInterface *n);

    NetInterface *getSourceInterface();
    NetInterface *getDestInterface();

    Node *getSourceNode();
    Node *getDestNode();
};

#endif
