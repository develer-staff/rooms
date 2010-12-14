#include "engine.h"
#include "roomsmanager.h"
#include "eventsmanager.h"
#include "event.h"
#include "action.h"
#include "drawdevice.h"
#include "area.h"

Engine *Engine::_engine = 0;

Engine::Engine()
{
    _rooms_mgr = new RoomsManager(this);
    _events_mgr = new EventsManager(this);
    if (_rooms_mgr == 0 || _events_mgr == 0)
    {
        log("ERROR: cannot create engine objects!", 1);
        exit(1);
    }
    _state = INITIALIZING;
}

Engine::~Engine()
{
    log("QUITTING ENGINE", 1);
    delete _rooms_mgr;
    delete _events_mgr;
}

Engine *Engine::createEngine()
{
    if (_engine == 0)
        _engine = new Engine();

    return _engine;
}

bool Engine::initialize()
{
    if (DEBUG_LEVEL)
    {
        std::ofstream log_file;
        log_file.open("rooms.log", std::ios::out);
        log_file.close();
    }

    if (!loadWorld("world.rooms"))
    {
        log("ERROR: cannot load world.rooms!", 1);
        exit(1);
        return false;
    }
    _state = GAME;
    return true;
}

void Engine::setDevice(DrawDevice *device)
{
    if (device != 0)
        _device = device;
    else
    {
        log("ERROR: cannot use a null graphic device!", 1);
        exit(1);
    }
}

void Engine::click (int x, int y)
{
    log("Mouse click received", 3);
    switch (_state)
    {
        case GAME:
        {
            //STUB
            std::string event;
            event = _rooms_mgr->eventAt(x, y);
            if (event == "")
                break;
            log("Event: " + event, 3);
            execActions(_events_mgr->actionsForEvent(event));
            break;
        }
    }
}

Engine::State Engine::state()
{
    return _state;
}

void Engine::loadGame(std::string filename)
{

}

bool Engine::loadWorld(std::string filename)
{
    //TODO: simplify this method
    try
    {
        log("Loading world from " + filename, 2);
        TiXmlDocument document(filename.c_str());
        //bool ok = document.LoadFile();
        int width = 0, height = 0;
        if (!xmlCheckDoc(&document)) throw "ERROR: wrong xml document!";
        TiXmlElement *root = document.RootElement();
        //Load World attributes
        log(root->Attribute("name"), 2);
        root->QueryIntAttribute("width", &width);
        root->QueryIntAttribute("height", &height);
        _rooms_mgr->size(width, height);
        _rooms_mgr->name(root->Attribute("name"));
        //TODO: manage different screen resolutions
        std::vector <TiXmlElement *> images =
            xmlGetAllChilds(root->FirstChildElement("images"), "img");
        std::vector <TiXmlElement *> rooms =
            xmlGetAllChilds(root->FirstChildElement("rooms"), "room");
        std::vector <TiXmlElement *> events =
            xmlGetAllChilds(root->FirstChildElement("events"), "event");
        std::vector <TiXmlElement *> items =
            xmlGetAllChilds(root->FirstChildElement("items"), "item");
        //Load Images
        for (std::vector<TiXmlElement *>::iterator i = images.begin();
             i != images.end(); i++)
            if (!_device->loadImage((*i)->Attribute("id"), (*i)->Attribute("file")))
                throw std::string("ERROR: cannot load image!").c_str();
        //Load Events
        for (std::vector<TiXmlElement *>::iterator i = events.begin();
             i != events.end(); i++)
        {
            Event *event = _events_mgr->addEvent((*i)->Attribute("id"));
            std::vector <TiXmlElement *> actions =
                xmlGetAllChilds((*i)->FirstChildElement("actions_if"), "action");
            for (std::vector<TiXmlElement *>::iterator j = actions.begin();
                 j != actions.end(); j++)
            {
                Action *act = event->addAction((*j)->Attribute("id"));
                std::vector <TiXmlElement *> params =
                    xmlGetAllChilds(*j, "param");
                for (std::vector<TiXmlElement *>::iterator z = params.begin();
                     z != params.end(); z++)
                    act->pushParam((*z)->Attribute("value"));
            }
        }
        //Load Rooms
        for (std::vector<TiXmlElement *>::iterator i = rooms.begin();
             i != rooms.end(); i++)
        {
            _rooms_mgr->addRoom((*i)->Attribute("id"), (*i)->Attribute("bg"));
            std::vector <TiXmlElement *> areas =
                xmlGetAllChilds((*i)->FirstChildElement("areas"), "area");
            for (std::vector<TiXmlElement *>::iterator j = areas.begin();
                 j != areas.end(); j++)
            {
                int area_x, area_y, area_w, area_h, area_enab;
                (*j)->QueryIntAttribute("x", &area_x);
                (*j)->QueryIntAttribute("y", &area_y);
                (*j)->QueryIntAttribute("width", &area_w);
                (*j)->QueryIntAttribute("height", &area_h);
                Area * a = _rooms_mgr->addArea((*j)->Attribute("id"),
                                    (*i)->Attribute("id"),
                                    area_x, area_y, area_w, area_h,
                                    (*j)->FirstChildElement("do_event")->Attribute("value"));
                (*j)->QueryIntAttribute("enabled", &area_enab);
                a->enabled(area_enab);
            }
        }
        //Load Items
        for (std::vector<TiXmlElement *>::iterator i = items.begin();
             i != items.end(); i++)
        {
            int area_x, area_y, area_w, area_h;
            (*i)->QueryIntAttribute("x", &area_x);
            (*i)->QueryIntAttribute("y", &area_y);
            (*i)->QueryIntAttribute("width", &area_w);
            (*i)->QueryIntAttribute("height", &area_h);
            _rooms_mgr->addItem((*i)->Attribute("id"),
                                (*i)->Attribute("room"),
                                area_x, area_y, area_w, area_h,
                                (*i)->FirstChildElement("do_event")->Attribute("value"),
                                (*i)->Attribute("image"));
        }
        //Goto start room
        std::string start_room = root->Attribute("start");
        apiRoomGoto(start_room);
        //TODO: load rest of world file
        return true;
    }
    catch (const char *msg)
    {
        log(msg, 1);
        return false;
    }
}

RoomsManager *Engine::getRoomsManager()
{
    return _rooms_mgr;
}

EventsManager *Engine::getEventsManager()
{
    return _events_mgr;
}

void Engine::execActions(std::vector <Action *> actions)
{
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); i++)
    {
        //TODO: think about improving this loop
        Action *act = *i;
        log("Exec action: " + act->id, 3);
        if (act->id == "ROOM_GOTO")
        {
            apiRoomGoto(act->popStrParam());
        } else if (act->id == "VAR_SET")
        {
            int var_value = act->popIntParam();
            std::string var_name = act->popStrParam();
            apiVarSet(var_name, var_value);
        } else if (act->id == "ITEM_MOVE")
        {
            std::string item_dest = act->popStrParam();
            std::string item_id = act->popStrParam();
            apiItemMove(item_id, item_dest);
        } else if (act->id == "AREA_SET_ENABLE")
        {
            int area_val = act->popIntParam();
            std::string area_id = act->popStrParam();
            apiAreaSetEnable(area_id, area_val);
        }
    }
}

void Engine::log(std::string text, int level)
{
    if (level <= DEBUG_LEVEL)
    {
        std::ofstream log_file;
        log_file.open("rooms.log", std::ios::out | std::ios::app);
        log_file << time(0) << ": " << text << '\n';
        log_file.close();
    }
}

void Engine::apiRoomGoto(std::string id)
{
    log("ROOM_GOTO: " + id, 2);
    _rooms_mgr->currentRoom(id);
}

void Engine::apiVarSet(std::string id, int value)
{
    log("VAR_SET: " + id, 2);
    _events_mgr->var(id, value);
}

void Engine::apiItemMove(std::string id, std::string dest)
{
    log("ITEM_MOVE: " + id + ", dest: " + dest, 2);
    _rooms_mgr->moveItem(id, dest);
}

void Engine::apiAreaSetEnable(std::string id, int value)
{
    bool bool_val = value;
    std::string str_val;
    bool_val ? str_val = "true" : str_val = "false";
    log("AREA_SET_ENABLE: " + id + ", enabled: " + str_val, 2);
    _rooms_mgr->area(id)->enabled(bool_val);
}

void Engine::exit(int status)
{
    if (_device)
        _device->quit(status);
}
