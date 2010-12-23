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
    class MockEngine: public Engine
    {
        public:
            void apiRoomGoto(const std::string name)
            {
                Engine::apiRoomGoto(name);
            }
            void apiVarSet(const std::string name, const int value)
            {
                Engine::apiVarSet(name, value);
            }
            void apiItemMove(const std::string name, const std::string dest)
            {
                Engine::apiItemMove(name, dest);
            }
    };
private:
    MockEngine *engine;
public:
    void setUp()
    {
        engine = new MockEngine;
        engine->getRoomsManager()->addRoom("room1", "");
        engine->getRoomsManager()->addRoom("room2", "");
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

    void testVarSet()
    {
        engine->apiVarSet("var1", 10);
        CPPUNIT_ASSERT(engine->getEventsManager()->var("var1") == 10);
    }

    void testItemMove()
    {
        Item *item = engine->getRoomsManager()->addItem("item1", "room1",
                                           10, 10, 10, 10, "", "");
        CPPUNIT_ASSERT(engine->getRoomsManager()->room("room1")->item("item1") == item);
        engine->apiItemMove("item1", "room2");
        CPPUNIT_ASSERT(engine->getRoomsManager()->room("room2")->item("item1") == item);
        CPPUNIT_ASSERT(engine->getRoomsManager()->room("room1")->item("item1") == 0);
    }

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ApiTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testRoomGoto",
                                       &ApiTests::testRoomGoto));
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testVarSet",
                                       &ApiTests::testVarSet));
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testItemMove",
                                       &ApiTests::testItemMove));
        return suiteOfTests;
    }
};

#endif // ENGINETESTS_H_INCLUDED
