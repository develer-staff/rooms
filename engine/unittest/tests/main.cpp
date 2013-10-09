#include "tests.h"

#include <cppunit/ui/text/TestRunner.h>

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ActionTests::suite());
    runner.addTest(RoomTests::suite());
    runner.addTest(ApiTests::suite());
    runner.addTest(WorldTests::suite());
    runner.addTest(XmlTests::suite());
    runner.addTest(AnimationsTest::suite());
    runner.addTest(ParserTest::suite());
    runner.run();
    return 0;
}
