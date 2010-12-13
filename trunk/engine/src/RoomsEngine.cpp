#include "RoomsEngine.h"
#include "RoomsManager.h"
#include "DrawDevice.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _rooms_mgr = new RoomsManager(this);
    _state = INITIALIZING;
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _rooms_mgr;
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
            std::string event = _rooms_mgr->eventAt(x, y);
            std::cout << event << '\n';
            if (event == "evento_lol")
                ROOM_GOTO("Cucina");
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
                        area->QueryIntAttribute("x", &area_x) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("y", &area_y) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("width", &area_w) == TIXML_SUCCESS ? ok &= true : ok = false;
                        area->QueryIntAttribute("height", &area_h) == TIXML_SUCCESS ? ok &= true : ok = false;
                        _rooms_mgr->addArea(id_area, id, area_x, area_y, area_w, area_h, "evento_lol");
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

void RoomsEngine::ROOM_GOTO(std::string id)
{
    //TODO: think about how to handle api errors
    _rooms_mgr->currentRoom(id);
}
