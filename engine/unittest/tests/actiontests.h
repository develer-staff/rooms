#ifndef ACTIONTESTS_H_INCLUDED
#define ACTIONTESTS_H_INCLUDED

#include "engine.h"

#include <cppunit/TestAssert.h> //CPPUNIT_ASSERT
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class ActionTests : public CppUnit::TestFixture
{
private:
    Action *act1;
public:
    void setUp()
    {
        act1 = new Action("test");
    }

    void tearDown()
    {
        delete act1;
    }

    void testPushPopStr()
    {
        act1->pushParam("lol");
        CPPUNIT_ASSERT("lol" == act1->popStrParam());
    }

    void testMultiPushPopStr()
    {
        act1->pushParam("lol");
        act1->pushParam("lol1");
        act1->pushParam("lol2");
        CPPUNIT_ASSERT("lol2" == act1->popStrParam());
        CPPUNIT_ASSERT("lol1" == act1->popStrParam());
        CPPUNIT_ASSERT("lol" == act1->popStrParam());
    }

    void testPushPopInt()
    {
        act1->pushParam("1234");
        CPPUNIT_ASSERT(1234 == act1->popIntParam());
    }

    void testMultiPushPopInt()
    {
        act1->pushParam("1234");
        act1->pushParam("2345");
        act1->pushParam("3546");
        CPPUNIT_ASSERT(3546 == act1->popIntParam());
        CPPUNIT_ASSERT(2345 == act1->popIntParam());
        CPPUNIT_ASSERT(1234 == act1->popIntParam());
    }

    void testWrongType()
    {
        act1->pushParam("lol");
        CPPUNIT_ASSERT(0 == act1->popIntParam());
    }

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ActionTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<ActionTests>("testPushPopStr",
                                       &ActionTests::testPushPopStr));
        suiteOfTests->addTest(new CppUnit::TestCaller<ActionTests>("testMultiPushPopStr",
                                       &ActionTests::testMultiPushPopStr));
        suiteOfTests->addTest(new CppUnit::TestCaller<ActionTests>("testPushPopInt",
                                       &ActionTests::testPushPopInt));
        suiteOfTests->addTest(new CppUnit::TestCaller<ActionTests>("testMultiPushPopInt",
                                       &ActionTests::testMultiPushPopInt));
        suiteOfTests->addTest(new CppUnit::TestCaller<ActionTests>("testWrongType",
                                       &ActionTests::testWrongType));
        return suiteOfTests;
    }
};

#endif // ACTIONTESTS_H_INCLUDED
