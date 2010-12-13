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
    if (_rooms_mgr == 0 || _events_mgr == 0)
    {
        log("ERROR: cannot create engine objects!", 1);
        exit(1);
    }
    _state = INITIALIZING;
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    log("QUITTING ENGINE", 1);
    delete _rooms_mgr;
    delete _events_mgr;
}

RoomsEngine *RoomsEngine::createEngine()
{
    if (_engine == 0)
        _engine = new RoomsEngine();

    return _engine;
}

bool RoomsEngine::initialize()
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

void RoomsEngine::setDevice(DrawDevice *device)
{
    if (device != 0)
        _device = device;
    else
    {
        log("ERROR: cannot use a null graphic device!", 1);
        exit(1);
    }
}

void RoomsEngine::click (int x, int y)
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

RoomsEngine::State RoomsEngine::state()
{
    return _state;
}

void RoomsEngine::loadGame(std::string filename)
{

}

bool RoomsEngine::loadWorld(std::string filename)
{
    //TODO: simplify this method
    try
    {
        log("Loading world from " + filename, 2);
        TiXmlDocument document(filename.c_str());
        bool ok = document.LoadFile();
        int width = 0, height = 0;
        if (!ok) throw "ERROR: cannot load xml document!";
        TiXmlElement *root = document.RootElement();
        TiXmlElement *node = 0;
        //Load World attributes
        _rooms_mgr->name(root->Attribute("name") ? root->Attribute("name") : "");
        root->QueryIntAttribute("width", &width) == TIXML_SUCCESS ? ok = true :
            throw "ERROR: missing world width attribute!";
        root->QueryIntAttribute("height", &height) == TIXML_SUCCESS ? ok = true :
            throw "ERROR: missing world height attribute!";
        _rooms_mgr->size(width, height);
        //TODO: manage different screen resolutions
        //Load images
        node = root->FirstChildElement("images");
        if (node)
            for (node = node->FirstChildElement("img"); node != 0;
                 node = node->NextSiblingElement("img"))
            {
                std::string id = "";
                std::string name = "";
                node->Attribute("id") ? id = node->Attribute("id") :
                    throw "ERROR: image has no id attribute!";
                node->Attribute("file") ? name = node->Attribute("file") :
                    throw "ERROR: image has no file attribute!";
                if (!_device->loadImage(id, name))
                {
                    throw std::string("ERROR: cannot load image " + name).c_str();
                }
            }
        //Load events
        node = root->FirstChildElement("events");
        if (node)
            for (node = node->FirstChildElement("event"); node != 0;
                 node = node->NextSiblingElement("event"))
            {
                std::string id = "";
                std::string name = "";
                node->Attribute("id") ? id = node->Attribute("id") :
                    throw "ERROR: event has no id attribute!";
                if (ok)
                {
                    Event *event = _events_mgr->addEvent(id);
                    TiXmlElement *action_el = node->FirstChildElement("actions_if");
                    for (action_el = action_el->FirstChildElement("action");
                         action_el != 0;
                         action_el = action_el->NextSiblingElement("action"))
                    {
                        Action *act = event->addAction(action_el->Attribute("id"));
                        TiXmlElement *param_el;
                        for (param_el = action_el->FirstChildElement("param");
                             param_el != 0;
                             param_el = param_el->NextSiblingElement("param"))
                                act->pushParam(param_el->Attribute("value"));
                    }
                }
            }
        //Load rooms
        node = root->FirstChildElement("rooms");
        if (node)
            for (node = node->FirstChildElement("room"); node != 0;
                 node = node->NextSiblingElement("room"))
            {
                std::string id = "";
                std::string bg = "";
                node->Attribute("id") ? id = node->Attribute("id") :
                    throw "ERROR: room has no id attribute!";
                node->Attribute("bg") ? bg = node->Attribute("bg") :
                    throw "ERROR: room has no bg attribute!";
                _rooms_mgr->addRoom(id, bg) ? ok =true :
                    throw "ERROR: cannot create room!";
                //Load
                TiXmlElement *area = node->FirstChildElement("areas");
                if (area)
                    for (area = area->FirstChildElement("area"); area != 0;
                         area = area->NextSiblingElement("area"))
                    {
                        std::string id_area;
                        if (node->Attribute("id") != 0)
                            id_area = node->Attribute("id");
                        else
                            throw "ERROR: area has no id attribute!";
                        int area_x, area_y, area_w, area_h;
                        TiXmlElement *doevent_el;
                        area->QueryIntAttribute("x", &area_x) == TIXML_SUCCESS ? ok = true :
                            throw "ERROR: area has no x attribute!";
                        area->QueryIntAttribute("y", &area_y) == TIXML_SUCCESS ? ok = true :
                            throw "ERROR: area has no y attribute!";
                        area->QueryIntAttribute("width", &area_w) == TIXML_SUCCESS ? ok = true :
                            throw "ERROR: area has no width attribute!";
                        area->QueryIntAttribute("height", &area_h) == TIXML_SUCCESS ? ok = true :
                            throw "ERROR: area has no height attribute!";
                        for (doevent_el = area->FirstChildElement("do_event");
                             doevent_el != 0;
                             doevent_el = doevent_el->NextSiblingElement("do_event"))
                        {
                            std::string id_event;
                            //TODO OPTIONAL: manage multi-events areas
                            if (doevent_el->Attribute("value") != 0)
                                id_event = doevent_el->Attribute("value");
                            else
                                throw "ERROR: do_event has no attribute value!";
                            _rooms_mgr->addArea(id_area, id, area_x, area_y, area_w, area_h, id_event);
                        }
                    }
            }
        //Goto start room
        std::string start_room = root->Attribute("start") ? root->Attribute("start") : "";
        if (start_room == "")
            throw "ERROR: there's no start room!";
        ROOM_GOTO(start_room);
        //TODO: load rest of world file
        return true;
    }
    catch (const char *msg)
    {
        log(msg, 1);
        return false;
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
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); i++)
    {
        //TODO: think about improving this loop
        Action *act = *i;
        log("Exec action: " + act->id, 3);
        if (act->id == "ROOM_GOTO")
        {
            ROOM_GOTO(act->popStrParam());
        } else if (act->id == "VAR_SET")
        {
            int var_value = act->popIntParam();
            std::string var_name = act->popStrParam();
            VAR_SET(var_name, var_value);
        }
    }
}

void RoomsEngine::log(std::string text, int level)
{
    if (level <= DEBUG_LEVEL)
    {
        std::ofstream log_file;
        log_file.open("rooms.log", std::ios::out | std::ios::app);
        log_file << time(0) << ": " << text << '\n';
        log_file.close();
    }
}

void RoomsEngine::ROOM_GOTO(std::string id)
{
    log("ROOM_GOTO: " + id, 2);
    _rooms_mgr->currentRoom(id);
}

void RoomsEngine::VAR_SET(std::string id, int value)
{
    log("VAR_SET: " + id, 2);
    _events_mgr->var(id, value);
}

void RoomsEngine::exit(int status)
{
    if (_device)
        _device->quit(status);
}
