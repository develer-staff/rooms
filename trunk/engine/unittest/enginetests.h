#ifndef ENGINETESTS_H_INCLUDED
#define ENGINETESTS_H_INCLUDED

#include "../src/engine.h"

#include <cppunit/TestAssert.h> //CPPUNIT_ASSERT
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class ApiTests : public CppUnit::TestFixture
{
private:
private:
    Engine *engine;
public:
    void setUp()
    {
        engine = createEngine();
        engine->getRoomsManager()->addRoom("room1");
        engine->getRoomsManager()->addRoom("room2");
        engine->getEventsManager()->addVar("var1", "10");
        engine->getRoomsManager()->addItem("item1", "room1",
                                           10, 10, 10, 10, "", "");
    }

    void testDown()
    {
        delete engine;
    }

    void testRoomGoto()
    {
        engine->apiRoomGoto("room1");
        CPPUNIT_ASSERT(engine->getRoomsManager()->currentRoom()->id == "room1");
    }

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ApiTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testRoomGoto",
                                       &ApiTests::testRoomGoto));
        return suiteOfTests;
    }
};

#endif // ENGINETESTS_H_INCLUDED
