#include <entity.hpp>
#include "myentity.hpp"

#include "catch.hpp"

using namespace MetaSim;

TEST_CASE("TestEntitySameName", "testName")
{
    std::unique_ptr<MyEntity> me(new MyEntity("name"));

    Entity *p = Entity::_find("name");
    REQUIRE( p == me.get() );
    REQUIRE( p == Entity::getPointer( me->getID() ) );
    
    try {
        MyEntity e2("name");
        REQUIRE( false );
    } catch (...) {
        REQUIRE( true );
    }
    p = Entity::getPointer( me->getID() + 1 );
    REQUIRE( p == 0 );
}

TEST_CASE("TestEntity.copy", "[entity][clone]")
{
    std::unique_ptr<EntityClone> p1(new EntityClone("cloned_entity"));

    auto p2 = p1->clone();

    REQUIRE(p1->getName() == "cloned_entity");
    std::stringstream ss;
    ss << "cloned_entity_copy_" << p1->getID() + 1;
    REQUIRE(p2->getName() == ss.str());
}
