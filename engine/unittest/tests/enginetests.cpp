#include "enginetests.h"

#if defined(_WIN32) || defined(ming)
    #define WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
#endif


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
                      "<world version='2' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<images><img file='../../../examples/example2/data/chiave.png' /></images>"
                      "<rooms><room id='room' bg='bg'></room></rooms>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../../../examples/example2/data/chiave.png' event='event' /></items>"
                      "<vars><var id='var' value='12' /></vars>"
                      "</world>\n";
    CPPUNIT_ASSERT(mock->loadWorldFromStr(xml));
    std::vector <std::pair <std::string, std::string> > items;
    items.push_back(std::make_pair("key", "room"));
    CPPUNIT_ASSERT(room_man->checkItemPlace(items) == true);
    std::vector <std::pair <std::string, int> > vars;
    vars.push_back(std::make_pair("var", 12));
    CPPUNIT_ASSERT(event_man->checkVarReqs(vars) == true);
}

void WorldTests::testReqsNo()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='2' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<images><img file='../../../examples/example2/data/chiave.png' /></images>"
                      "<rooms><room id='room' bg='bg'></room></rooms>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../../../examples/example2/data/chiave.png' event='event' /></items>"
                      "<vars><var id='var' value='20' /></vars>"
                      "</world>\n";
    CPPUNIT_ASSERT(mock->loadWorldFromStr(xml));
    std::vector <std::pair <std::string, std::string> > items;
    items.push_back(std::make_pair("key", "wrong_room"));
    CPPUNIT_ASSERT(room_man->checkItemPlace(items) == false);
    std::vector <std::pair <std::string, int> > vars;
    vars.push_back(std::make_pair("var", 35));
    CPPUNIT_ASSERT(event_man->checkVarReqs(vars) == false);
}

void WorldTests::testLoadWorld()
{
    std::string xml = "<?xml version='1.0' ?>"
                      "<world version='2' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<images><img file='../../../examples/example2/data/chiave.png'/></images>"
                      "<items><item id='key' room='room' x='10' y='10' width='50' height='50' image='../../../examples/example2/data/chiave.png' event='event' /></items>"
                      "<vars /><dialogs />"
                      "<events><event id='event'>"
                      "<action id='ROOM_GOTO'><param value='room' />"
                      "<animations><animation object='room' duration='500' easing='LINEAR'><property name='x' from='0.0' to='0.5' /></animation></animations>"
                      "</action>"
                      "</event></events>"
                      "<rooms><room id='room' bg='bg'><area id='id' x= '10' y='10' width='10' height='10' event='event'/></room></rooms>"
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
                      "<world version='2' name='testLoadWorld' width='800' height='600' start='room'>"
                      "<rooms><room id='room' bg='bg' /></rooms>"
                      "<images><img file='../../../examples/example2/data/chiave.png'/></images>"
                      "<dialogs><dialog id='dialog'start='firststep'><step id='firststep' text='text'></step></dialog></dialogs>"
                      "</world>\n";
    mock->loadWorldFromStr(xml);
    mock->apiDialogStart("dialog");
    CPPUNIT_ASSERT(mock->getDialogText() == "text");
    CPPUNIT_ASSERT(mock->state() == Engine::DIALOG);

}


void AnimationsTest::setUp()
{

    anim_mgr = new AnimationsManager();
}

void AnimationsTest::tearDown()
{
    delete anim_mgr;
}

void AnimationsTest::testAnimations()
{
    std::vector<Animation *> animations;

    Animation *linear = new Animation("linear", 10000);
    linear->setEasing(Animation::LINEAR);
    linear->addProperty("x", 0, 100);
    linear->addProperty("y", 0, 100);
    linear->addProperty("width", 0, 100);
    linear->addProperty("height", 0, 100);
    linear->addProperty("alpha", 0, 1);
    animations.push_back(linear);

    anim_mgr->addAnimations(animations);
    CPPUNIT_ASSERT(anim_mgr->hasAnimations());

    anim_mgr->startAnimations();
    CPPUNIT_ASSERT(anim_mgr->isAnimating());

    GuiData data;
    data.alpha = 0;
    data.rect = GuiRect(0,0,0,0);
    data.image = "";
    data.text = "";

#ifdef WINDOWS
    Sleep(1000);
#else
    sleep(1);
#endif

    int time = updateAndGetTime("linear", &data);
    int expected_data = time / 100;
    CPPUNIT_ASSERT(data.rect.x == expected_data);

    CPPUNIT_ASSERT(data.rect.y == expected_data);
    CPPUNIT_ASSERT(data.rect.w == expected_data);
    CPPUNIT_ASSERT(data.rect.h == expected_data);
    CPPUNIT_ASSERT(data.alpha == (time * 255) / 10000);
}

int AnimationsTest::updateAndGetTime(std::string id, GuiData *data)
{
    anim_mgr->updateObjectState(id, data);
    return anim_mgr->timer->elapsed();
}
