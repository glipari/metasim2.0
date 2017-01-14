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
/*
 * $Id$
 *
 * $Log$
 */

#ifndef __PARTICLE_HPP__
#define __PARTICLE_HPP__

namespace MetaSim {

    class Event;
    
    /**
       \ingroup metasim

       @{
    */
    /**
       An abstract class, only to specify the interface of a
       particle. It is used in Event class to create lists of particles.
    */
    class ParticleInterface {
    public:
        virtual ~ParticleInterface() {};

        virtual void probe() = 0;

        virtual void clone_to(Event &e) = 0;
    };

    /**
       A particle is a function object whose only job is to
       "connect" an event of a certain type (template parameter E) to a
       statistical object (see basestat.hpp) or to a trace object
       (template parameter S).  The user only needs to call the
       constructor to create a particle and add it to an event.

       The particle has been provided to avoid the need for
       dynamic_casts in the statistical objects and in the tracing
       objects. 

       However, the code below is so small, simple and general (two
       functions!) that it can be reused in any context. The only
       requirement is that 

       -1) class E has a method named
           addParticle(ParticleInterface *), 
       -2) and class S has a method called
           probe(E &). 

       \b WARNING : if the second condition does not hold, user
          could get horrible error messages!
    */
    template<class E, class S>
    class Particle : public ParticleInterface {
    private:
        E *evtptr_;
        S *staptr_;
    public:
        /**
           Particle constructor. This constructor automatically inserts
           the particle in the event by calling the
           Event::addParticle(this) method.  The owner of the object
           becomes the event to which this particle has been
           added. Therefore, 

           - it is the Event responsibility to destruct the particle 
           (it is done in the Event base class destructor)

           - it is forbidden to add the same particle to two different
           events (however, we do not check this, cause it would be too
           much of a hassle). If you need to collect the same statistic
           from two events, create two particles, the memory overhead is
           much smaller compared to the code and data structures needed to 
           add a reference counter.
      
           An example of usage can be found in examples/queue/queue.cpp
       
           @param e  reference to the event to be traced.
           @param s  reference to the tracing object. 
        */
        Particle(E &e, S &s) 
            : evtptr_(&e), staptr_(&s) {
        }

        virtual ~Particle() {}
    
        virtual void probe() {
            staptr_->probe(*evtptr_);
        }

        /**
           Copies a particle to a new event. It uses a static_cast<>
           to force type of event. This is not clean, but for the
           moment I could not find anything better than this.
         */
        virtual void clone_to(Event &e) {
            E& ent = static_cast<E&>(e);
            std::unique_ptr< ParticleInterface > p(new Particle<E, S>(ent, *staptr_));
            ent.addParticle(std::move(p));
        }
    };

    template<class Evt, class StatClass>
    void attach_stat(StatClass &s, Evt &e) {
        std::unique_ptr< ParticleInterface > p(new Particle<Evt, StatClass>(e, s));
        e.addParticle(std::move(p));
    }
    /**
       @}
    */
}
#endif
