#ifndef ENGINETESTS_H_INCLUDED
#define ENGINETESTS_H_INCLUDED

#include "../src/engine.h"

#include <string>
#include <utility> // std::pair
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
        using Engine::apiDialogStart;
};

class WorldTests : public CppUnit::TestFixture
{
private:
    MockEngine *mock;
    RoomsManager *room_man;
    EventsManager *event_man;
public:
    void setUp();
    void tearDown();
    void testLoadWorld();
    void testReqsOk();
    void testReqsNo();

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "WorldTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<WorldTests>("testLoadWorld",
                                       &WorldTests::testLoadWorld));
        suiteOfTests->addTest(new CppUnit::TestCaller<WorldTests>("testReqsOk",
                                       &WorldTests::testReqsOk));
        suiteOfTests->addTest(new CppUnit::TestCaller<WorldTests>("testReqsNo",
                                       &WorldTests::testReqsNo));
        return suiteOfTests;
    }
};

class ApiTests : public CppUnit::TestFixture
{
private:
    MockEngine *mock;
    RoomsManager *room_man;
public:
    void setUp();
    void tearDown();
    void testRoomGoto();
    void testVarSet();
    void testItemMove();
    void testDialogStart();

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ApiTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testRoomGoto",
                                       &ApiTests::testRoomGoto));
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testVarSet",
                                       &ApiTests::testVarSet));
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testItemMove",
                                       &ApiTests::testItemMove));
        suiteOfTests->addTest(new CppUnit::TestCaller<ApiTests>("testDialogStart",
                                       &ApiTests::testDialogStart));
        return suiteOfTests;
    }
};

#endif // ENGINETESTS_H_INCLUDED
