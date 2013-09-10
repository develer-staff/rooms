#ifndef XMLTESTS_H_INCLUDED
#define XMLTESTS_H_INCLUDED

#include "../src/engine.h"

#include <cppunit/TestAssert.h> //CPPUNIT_ASSERT
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

class XmlTests : public CppUnit::TestFixture
{
public:
    void setUp()
    {
    }

    void tearDown()
    {
    }

    void testGoodDoc()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<images /> <rooms /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testGoodImages()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<images><img file='file' /></images>"
                   "<rooms /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongImages()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<images><img /></images>"
                   "<rooms /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testGoodRooms()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg' /></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongRooms()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' /></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testGoodEvents()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<events><event id='id'></events>"
                   "<images /> <rooms /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongEvents()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<events><event /></events>"
                   "<images /> <rooms /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testGoodVars()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<vars><var id='id' value='10'></vars>"
                   "<images /> <rooms /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongVars()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<vars><var id='id' value='AB'></vars>"
                   "<images /> <rooms /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testGoodAreas()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg'><area id='id' x='10' y='10' width='10' height='10'>"
                   "<do_event value='event' /></area></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongAreas()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg'><areas><area id='id' y='10' width='10' height='10'>"
                   "<do_event value='event' /></area></areas></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testGoodDialogs()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<dialogs><dialog id='dialog' start='0'><step id='0' text='text'><link id='-1' text='exit'</step></dialogs>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        CPPUNIT_ASSERT(reader.loadFromStr(xml) && reader.parse());
    }

    void testWrongDialogs()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='2' name='name' width='800' height='600' start='room'>"
                   "<dialogs><dialog start='0'><step id='0' text='text'><link id='-1' text='exit'</step></dialogs>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(!reader.parse());
    }

    void testUpgrade1to2()
    {
        std::string xml = "<?xml version='1.0' ?>"
                   "<world version='1' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg'><area id='id' x='100' y='60' width='50' height='90'>"
                   "<images /> <events /> <items />"
                   "</world>\n";
        RoomsReader reader;
        reader.loadFromStr(xml);
        CPPUNIT_ASSERT(reader.parse());
        RRNode *node = reader.getCrawler();
        node->gotoElement("area");
        CPPUNIT_ASSERT(!node->isNull());
        CPPUNIT_ASSERT(node->attrFloat("x") == 0.125f);

        CPPUNIT_ASSERT(node->attrFloat("y") == 0.1f);
        CPPUNIT_ASSERT(node->attrFloat("width") == 0.0625f);
        CPPUNIT_ASSERT(node->attrFloat("height") == 0.15f);
    }


    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "XmlTests" );
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodDoc",
                                       &XmlTests::testGoodDoc));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodImages",
                                       &XmlTests::testGoodImages));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongImages",
                                       &XmlTests::testWrongImages));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodRooms",
                                       &XmlTests::testGoodRooms));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongRooms",
                                       &XmlTests::testWrongRooms));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodEvents",
                                       &XmlTests::testGoodEvents));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongEvents",
                                       &XmlTests::testWrongEvents));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodVars",
                                       &XmlTests::testGoodEvents));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongVars",
                                       &XmlTests::testWrongEvents));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodAreas",
                                       &XmlTests::testGoodAreas));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongAreas",
                                       &XmlTests::testWrongAreas));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testGoodDialogs",
                                       &XmlTests::testGoodDialogs));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testWrongDialogs",
                                       &XmlTests::testWrongDialogs));
        suiteOfTests->addTest(new CppUnit::TestCaller<XmlTests>("testUpgrade1to2",
                                       &XmlTests::testUpgrade1to2));
        return suiteOfTests;
    }
};

#endif // XMLTESTS_H_INCLUDED

