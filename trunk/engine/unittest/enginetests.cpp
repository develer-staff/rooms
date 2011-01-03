#include "enginetests.h"


void WorldTests::setUp()
{
    mock = new MockEngine;
    room_man = mock->getRoomsManager();
    event_man = mock->getEventsManager();
}

void WorldTests::tearDown()
{
    delete mock;
}

void WorldTests::testReqsOk()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='ROOMS_VANILLA' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<rooms><room id='room' bg='bg'><areas /></room></rooms>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../example/example2/data/chiave.png'><do_event value='event' /></item></items>"
                      "<vars><var id='var' value='1' /></vars>"
                      "</world>\n";
    mock->loadWorldFromStr(xml);
    std::vector <std::pair <std::string, std::string> > items;
    items.push_back(std::make_pair("key", "room"));
    CPPUNIT_ASSERT(room_man->checkItemPlace(items) == true);
    std::vector <std::pair <std::string, int> > vars;
    vars.push_back(std::make_pair("var", 1));
    CPPUNIT_ASSERT(event_man->checkVarReqs(vars) == true);
}

void WorldTests::testReqsNo()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='ROOMS_VANILLA' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<rooms><room id='room' bg='bg'><areas /></room></rooms>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../example/example2/data/chiave.png'><do_event value='event' /></item></items>"
                      "<vars><var id='var' value='1' /></vars>"
                      "</world>\n";
    mock->loadWorldFromStr(xml);
    std::vector <std::pair <std::string, std::string> > items;
    items.push_back(std::make_pair("key", "wrong_room"));
    CPPUNIT_ASSERT(room_man->checkItemPlace(items) == false);
    std::vector <std::pair <std::string, int> > vars;
    vars.push_back(std::make_pair("var", 0));
    CPPUNIT_ASSERT(event_man->checkVarReqs(vars) == false);
}

void WorldTests::testLoadWorld()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='ROOMS_VANILLA' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<rooms><room id='room' bg='bg'><areas><area id='id' x= '10' y='10' width='10' height='10'>"
                      "<do_event value='event' /></area></areas></room></rooms>"
                      "<images><img file='../example/example2/data/chiave.png'/></images>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../example/example2/data/chiave.png'><do_event value='event' /></item></items>"
                      "<events><event id='event'><requirements></requirements><actions_if><action id='ROOM_GOTO'/><param value='room' /></actions_if></event></events>"
                      "</world>\n";
    CPPUNIT_ASSERT(mock->loadWorldFromStr(xml));
    CPPUNIT_ASSERT(room_man->room("room") != 0);
    CPPUNIT_ASSERT(room_man->item("key") != 0);
    CPPUNIT_ASSERT(event_man->event("event") != 0);
    CPPUNIT_ASSERT(room_man->eventAt(15, 15) == "event");
}


void ApiTests::setUp()
{
    mock = new MockEngine;
    room_man = mock->getRoomsManager();
    room_man->addRoom("room1", "");
    room_man->addRoom("room2", "");
}

void ApiTests::tearDown()
{
    delete mock;
}

void ApiTests::testRoomGoto()
{
    mock->apiRoomGoto("room1");
    CPPUNIT_ASSERT(room_man->currentRoom()->id == "room1");
}

void ApiTests::testVarSet()
{
    mock->apiVarSet("var1", 10);
    CPPUNIT_ASSERT(mock->getEventsManager()->var("var1") == 10);
}

void ApiTests::testItemMove()
{
    Item *item = room_man->addItem("item1", "room1",
                                       10, 10, 10, 10, "", "");
    CPPUNIT_ASSERT(room_man->room("room1")->item("item1") == item);
    mock->apiItemMove("item1", "room2");
    CPPUNIT_ASSERT(room_man->room("room2")->item("item1") == item);
    CPPUNIT_ASSERT(room_man->room("room1")->item("item1") == 0);
}

void ApiTests::testDialogStart()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='ROOMS_VANILLA' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<rooms><room id='room' bg='bg' /></rooms>"
                      "<images><img file='../example/example2/data/chiave.png'/></images>"
                      "<dialogs><dialog id='dialog'start='firststep'><step id='firststep' text='text'></step></dialog></dialogs>"
                      "</world>\n";
    mock->loadWorldFromStr(xml);
    mock->apiDialogStart("dialog");
    CPPUNIT_ASSERT(mock->getDialogText() == "text");
    CPPUNIT_ASSERT(mock->state() == Engine::DIALOG);

}
