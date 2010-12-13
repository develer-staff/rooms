#include "roomsengine.h"
#include "roomsmanager.h"
#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "drawdevice.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _rooms_mgr = new RoomsManager(this);
    _events_mgr = new EventsManager(this);
    _state = INITIALIZING;
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _rooms_mgr;
    delete _events_mgr;
}

RoomsEngine *RoomsEngine::createEngine()
{
    if (_engine == 0)
    {
        _engine = new RoomsEngine();
    }
    return _engine;
}

int RoomsEngine::initialize()
{
    /*if (!loadWorld("test_world.rooms"))
        throw;  //TODO: handle exception*/
    loadWorld("world.rooms");
    _state = GAME;
}

void RoomsEngine::setDevice(DrawDevice *device)
{
    device != 0 ? _device = device : throw; //TODO: handle error!
}

#include <iostream>

void RoomsEngine::click (int x, int y)
{
    switch (_state)
    {
        case GAME:
        {
            //STUB
            std::string event;
            event = _rooms_mgr->eventAt(x, y);
            if (event == "")
                break;
            std::cout << event << '\n';
            execActions(_events_mgr->actionsForEvent(event));
            break;
        }
    }
}

RoomsEngine::State RoomsEngine::state()
{
    return _state;
}

void RoomsEngine::loadGame(std::string filename)
{

}

bool RoomsEngine::loadWorld(std::string filename)
{
    //TODO: realize a better error management than ok &= true
    //TODO: handle every exception
    //TODO: simplify this method
    TiXmlDocument document(filename.c_str());
    bool ok = document.LoadFile();
    int width = 0, height = 0;
    if (ok)
    {
        TiXmlElement *root = document.RootElement();
        TiXmlElement *node = 0;
        //Load World attributes
        _rooms_mgr->name(root->Attribute("name") ? root->Attribute("name") : "");
        root->QueryIntAttribute("width", &width) == TIXML_SUCCESS ? ok &= true : ok = false;
        root->QueryIntAttribute("height", &height) == TIXML_SUCCESS ? ok &= true : ok = false;
        _rooms_mgr->size(width, height);
        //TODO: manage different screen resolutions
        //Load images
        (node = root->FirstChildElement("images")) != 0 ? ok &= true : ok = false;
        for (node = node->FirstChildElement("img"); node != 0; node = node->NextSiblingElement("img"))
        {
            std::string id = "";
            std::string name = "";
            id = node->Attribute("id");
            name = node->Attribute("file");
            if (ok)
                ok = (_device->loadImage(id, name));
        }
        //Load events
        (node = root->FirstChildElement("events")) != 0 ? ok &= true : ok = false;
        for (node = node->FirstChildElement("event"); node != 0; node = node->NextSiblingElement("event"))
        {
            std::string id = "";
            std::string name = "";
            id = node->Attribute("id");
            if (ok)
            {
                Event *event = _events_mgr->addEvent(id);
                TiXmlElement *action_el = node->FirstChildElement("actions_if");
                for (action_el = action_el->FirstChildElement("action"); action_el != 0; action_el = action_el->NextSiblingElement("action"))
                {
                    Action *act = event->addAction(action_el->Attribute("id"));
                    TiXmlElement *param_el;
                    for (param_el = action_el->FirstChildElement("param"); param_el != 0; param_el = param_el->NextSiblingElement("param"))
                    {
                        act->pushParam(param_el->Attribute("value"));
                    }
                }
            }
        }
        //Load rooms
        (node = root->FirstChildElement("rooms")) != 0 ? ok &= true : ok = false;
        for (node = node->FirstChildElement("room"); node != 0; node = node->NextSiblingElement("room"))
        {
            std::string id = "";
            std::string bg = "";
            id = node->Attribute("id");
            bg = node->Attribute("bg");
            if (ok)
            {
                _rooms_mgr->addRoom(id, bg) ? ok &=true : ok = false;
                //Load
                TiXmlElement *area = node->FirstChildElement("areas");
                if (area)
                    for (area = area->FirstChildElement("area"); area != 0; area = area->NextSiblingElement("area"))
                    {
                        std::string id_area = node->Attribute("id");
                        int area_x, area_y, area_w, area_h;
                        TiXmlElement *doevent_el;
                        area->QueryIntAttribute("x", &area_x) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("y", &area_y) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("width", &area_w) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("height", &area_h) == TIXML_SUCCESS ? ok &= true : ok = false;
                        for (doevent_el = area->FirstChildElement("do_event"); doevent_el != 0; doevent_el = doevent_el->NextSiblingElement("do_event"))
                        {
                            //TODO OPTIONAL: manage multi-events areas
                            std::string id_event = doevent_el->Attribute("value");
                            _rooms_mgr->addArea(id_area, id, area_x, area_y, area_w, area_h, id_event);
                        }
                    }
            }
        }
        //Goto start room
        ROOM_GOTO(root->Attribute("start") ? root->Attribute("start") : "");
        //TODO: load rest of world file
        return ok;
    } else {
        return ok;
    }
}

RoomsManager *RoomsEngine::getRoomsManager()
{
    return _rooms_mgr;
}

EventsManager *RoomsEngine::getEventsManager()
{
    return _events_mgr;
}

void RoomsEngine::execActions(std::vector <Action *> actions)
{
    std::cout << actions[0]->id << '\n';
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); i++)
    {
        //TODO: think about improving this loop
        Action *act = *i;
        if (act->id == "ROOM_GOTO")
        {
            ROOM_GOTO(act->popStrParam());
        }
    }
}

void RoomsEngine::ROOM_GOTO(std::string id)
{
    //TODO: think about how to handle api errors
    _rooms_mgr->currentRoom(id);
}
