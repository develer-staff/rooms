#ifndef ENGINETESTS_H_INCLUDED
#define ENGINETESTS_H_INCLUDED

#include "../src/engine.h"

#include <cppunit/TestAssert.h> //CPPUNIT_ASSERT
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

//Unit Test Class

class MockEngine : public Engine
{
    public:
        using Engine::apiItemMove;
        using Engine::apiRoomGoto;
        using Engine::apiVarSet;
};

class ApiTests : public CppUnit::TestFixture
{
private:
    MockEngine *mock;
    RoomsManager *room_man;
public:
    void setUp()
    {
        mock = new MockEngine;
        room_man = mock->getRoomsManager();
        room_man->addRoom("room1", "");
        room_man->addRoom("room2", "");
    }

    void tearDown()
    {
        delete mock;
    }

    void testRoomGoto()
    {
        mock->apiRoomGoto("room1");
        CPPUNIT_ASSERT(room_man->currentRoom()->id == "room1");
    }

    void testVarSet()
    {
        mock->apiVarSet("var1", 10);
        CPPUNIT_ASSERT(mock->getEventsManager()->var("var1") == 10);
    }

    void testItemMove()
    {
        Item *item = room_man->addItem("item1", "room1",
                                           10, 10, 10, 10, "", "");
        CPPUNIT_ASSERT(room_man->room("room1")->item("item1") == item);
        mock->apiItemMove("item1", "room2");
        CPPUNIT_ASSERT(room_man->room("room2")->item("item1") == item);
        CPPUNIT_ASSERT(room_man->room("room1")->item("item1") == 0);
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
