/*
 * myentity.hpp
 *
 *  Created on: Mar 14, 2011
 *      Author: lipari
 */

#ifndef MYENTITY_HPP_
#define MYENTITY_HPP_

#include <entity.hpp>
#include <gevent.hpp>
#include <cloneable.hpp>

using namespace MetaSim;

class MyEntity : public MetaSim::Entity {
    bool afirst;
    bool bfirst;
    
    int count;

public:

    MetaSim::GEvent<MyEntity> eventA;
    MetaSim::GEvent<MyEntity> eventB;
    MetaSim::GEvent<MyEntity> eventC;
    
    MyEntity();
    MyEntity(const std::string &n);
    MyEntity(const MyEntity &obj) :
        Entity(obj),
        eventA(obj.eventA, *this),
        eventB(obj.eventB, *this),
        eventC(obj.eventC, *this)
        {}
    
    void onEventA(MetaSim::Event *);
    void onEventB(MetaSim::Event *);
    void onEventC(MetaSim::Event *);
    
    void newRun();
    void endRun();
    bool isAFirst();
    int getCounter();
};


class CloneableEntity : public MyEntity {
protected:
    CloneableEntity(const CloneableEntity &obj) : MyEntity(obj) {}
public:
    using MyEntity::MyEntity;
    
    BASE_CLONEABLE(CloneableEntity)
};

class EntityClone : public CloneableEntity {
protected:
    EntityClone(const EntityClone &obj) : CloneableEntity(obj) {}
public:
    using CloneableEntity::CloneableEntity;
    
    CLONEABLE(CloneableEntity, EntityClone)
};

#endif /* MYENTITY_HPP_ */
