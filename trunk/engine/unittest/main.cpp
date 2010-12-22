#include "tests.h"

#include <cppunit/ui/text/TestRunner.h>

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ActionTests::suite());
    runner.addTest(RoomTests::suite());
    runner.run();
    return 0;
}
