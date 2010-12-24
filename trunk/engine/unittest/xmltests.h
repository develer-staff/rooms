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
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<images /> <rooms /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testGoodImages()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<images><img file='file' /></images>"
                   "<rooms /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testWrongImages()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<images><img /></images>"
                   "<rooms /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(!xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testGoodRooms()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg' /></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testWrongRooms()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' /></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(!xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testGoodEvents()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<events><event id='id'></events>"
                   "<images /> <rooms /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testWrongEvents()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<events><event /></events>"
                   "<images /> <rooms /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(!xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testGoodVars()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<vars><var id='id' value='10'></vars>"
                   "<images /> <rooms /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testWrongVars()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<vars><var id='id' value='AB'></vars>"
                   "<images /> <rooms /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(!xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testGoodAreas()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg'><areas><area id='id' x='10' y='10' width='10' height='10'>"
                   "<do_event value='event' /></area></areas></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(xml::xmlCheckDoc(&doc, Engine::VERSION));
    }

    void testWrongAreas()
    {
        TiXmlDocument doc;
        doc.Parse("<?xml version='1.0' ?>"
                   "<world version='ROOMS_VANILLA' name='name' width='800' height='600' start='room'>"
                   "<rooms><room id='id' bg='bg'><areas><area id='id' y='10' width='10' height='10'>"
                   "<do_event value='event' /></area></areas></rooms>"
                   "<images /> <events /> <items />"
                   "</world>\n", 0, TIXML_ENCODING_UTF8);
        CPPUNIT_ASSERT(!xml::xmlCheckDoc(&doc, Engine::VERSION));
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
        return suiteOfTests;
    }
};

#endif // XMLTESTS_H_INCLUDED

