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
    // destination interface
    NetInterface *_dst_net_interf;
    // source interface 
    NetInterface *_src_net_interf;

public:

    // constructor
    Message(int l, Node *s, Node *d);

    // set the starting time of the message
    void setStartTime(MetaSim::Tick t);
    MetaSim::Tick getStartTime();

    // transmission time
    void setTransTime(MetaSim::Tick t);
    MetaSim::Tick getTransTime();

    // arrival time
    void setArrTime(MetaSim::Tick t);
    MetaSim::Tick getArrTime();

    // message lenght
    int getLength();

    
    void setSourceInterface(NetInterface *n);
    void setDestInterface(NetInterface *n);

    NetInterface *getSourceInterface();
    NetInterface *getDestInterface();

    Node *getSourceNode();
    Node *getDestNode();
};

#endif
