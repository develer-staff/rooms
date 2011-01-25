#ifndef ROOMSTEST_H_INCLUDED
#define ROOMSTEST_H_INCLUDED

#include "../src/engine.h"

#include <cppunit/TestAssert.h> //CPPUNIT_ASSERT
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class RoomTests : public CppUnit::TestFixture
{
private:
    Room *room1;
    Item *item1;
public:
    void setUp()
    {
        room1 = new Room("room");
        item1 = new Item("item");
        item1->setSize(10, 0, 10, 10);
    }

    void tearDown()
    {
        delete item1;
        delete room1;
    }

    void testAddArea()
    {
        Area *area = room1->addArea("area");
        CPPUNIT_ASSERT(room1->area("area") == area);
    }

    void testWrongArea()
    {
        CPPUNIT_ASSERT(room1->area("wrong") == 0);
    }

    void testAddItem()
    {
        room1->addItem("item", item1);
        CPPUNIT_ASSERT(room1->item("item") == item1);
        CPPUNIT_ASSERT(room1->items().size() == 1);
    }

    void testWrongItem()
    {
        CPPUNIT_ASSERT(room1->item("wrong") == 0);
    }

    void testRemItem()
    {
        room1->addItem("item", item1);
        room1->remItem("item");
        CPPUNIT_ASSERT(room1->item("item") == 0);
        CPPUNIT_ASSERT(room1->items().size() == 0);
    }

    void testItemAt()
    {
        room1->addItem("item", item1);
        CPPUNIT_ASSERT(room1->itemAt(15, 5) == item1);
        CPPUNIT_ASSERT(room1->itemAt(-1, -1) == 0);
    }

    void testAreaAt()
    {
        Area *area = room1->addArea("area");
        area->setSize(0, 0, 10, 10);
        CPPUNIT_ASSERT(room1->areaAt(5, 5) == area);
        CPPUNIT_ASSERT(room1->areaAt(-1, -1) == 0);
    }

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "RoomTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testAddArea",
                                       &RoomTests::testAddArea));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testWrongArea",
                                       &RoomTests::testWrongArea));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testAddItem",
                                       &RoomTests::testAddItem));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testWrongItem",
                                       &RoomTests::testWrongItem));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testRemItem",
                                       &RoomTests::testRemItem));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testItemAt",
                                       &RoomTests::testItemAt));
        suiteOfTests->addTest(new CppUnit::TestCaller<RoomTests>("testAreaAt",
                                       &RoomTests::testAreaAt));
        return suiteOfTests;
    }
};

#endif // ROOMSTEST_H_INCLUDED
