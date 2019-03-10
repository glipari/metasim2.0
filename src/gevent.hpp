/***************************************************************************
    begin                : Thu Apr 24 15:54:58 CEST 2003
    copyright            : (C) 2003 by Giuseppe Lipari
    email                : lipari@sssup.it
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef __GEVENT_HPP__
#define __GEVENT_HPP__

#include <event.hpp>

namespace MetaSim {
    /**
       \ingroup metasim_ee

       This template class is used for simplifying the writing of a
       system model. Most of the times, the doit() method of an event
       must only call a handler method of some class. Normally, you must
       write a new class derived from event and override the virtual
       doit() method. However, it is a lot of repetitive work! And when
       there is a lot of repetitive work to do, template is the
       solution!

       The GEvent class takes a class derived from Entity as a template
       argument. Then, template function register_handler() must be
       called passing the pointer to the handler before using this
       event.

       An example of usage is found in example/eth/netinterface.hpp:

       \dontinclude netinterface.hpp
       \skipline class EthernetInterface
       \until EthernetInterface(

       The _trans_evt event object is of type GEvent<X>: there is not
       need of defining a special class derived from event. The
       constructor for EthernetInterface must invoke the
       register_handler() function:

       \dontinclude netinterface.cpp
       \skipline EthernetInterface::EthernetInterface
       \until register_handler

       Handler onTransmit() is called whenever the event is triggered.
    */
    template<class X>
    class GEvent : public Event {
        typedef void (X::* Pmemfun)(Event *);
        
        X *_obj;
        Pmemfun _fun;
        
    public:

        /** The constructor takes the pointer to the object, the
            address of a member function and the priority of the event.
        */
        GEvent(X *obj, typename GEvent<X>::Pmemfun fun, int p = Event::_DEFAULT_PRIORITY) :
            Event(p), _obj(obj), _fun(fun) {}
        
        /**
           A copy constructor. Useful when creating many events of the
           same type for the same \b object. (Remember: all these
           events point to the same object!)
        */
        GEvent(const GEvent<X> &e) : Event(e), _obj(e._obj), _fun(e._fun) {} 

        /** A more generic constructor: the new copied event points to
         * a different object of the same type, the function to be
         * called is the same */
        GEvent(const GEvent<X> &e, X& obj) : Event(e), _obj(&obj), _fun(e._fun) {}
        
        /**
           Simply calls the specified handler on the specified object.
        */
        virtual void doit() { 
            if ((_obj != nullptr) && (_fun != nullptr))
                (_obj->*_fun)(this);
        }
    };
}  

#endif
