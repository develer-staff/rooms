#include "engine.h"

Engine *Engine::engine = 0;

Engine::Engine()
{
    try
    {
        rooms_mgr = new RoomsManager(this);
        events_mgr = new EventsManager(this);
        _state = INITIALIZING;
        if (DEBUG_LEVEL)
        {
            std::ofstream log_file;
            log_file.open("rooms.log", std::ios::out);
            log_file.close();
        }
    }
    catch (...)
    {
        log("ERROR: cannot create a valid engine!", 1);
        exit();
    }
}

Engine::~Engine()
{
    log("QUITTING ENGINE", 1);
    delete rooms_mgr;
    delete events_mgr;
}

Engine *Engine::createEngine()
{
    if (engine == 0)
        engine = new Engine();

    return engine;
}

void Engine::exit()
{
    delete engine;
}

void Engine::click (const int x, const int y)
{
    log("Mouse click received", 3);
    switch (_state)
    {
        case GAME:
        {
            string event;
            event = rooms_mgr->eventAt(x, y);
            if (event == "")
                break;
            log("Event: " + event, 3);
            execActions(events_mgr->actionsForEvent(event));
            break;
        }
    }
}

Engine::State Engine::state() const
{
    return _state;
}

void Engine::state(const Engine::State state_name)
{
    _state = state_name;
}

void Engine::loadGame(const string filename)
{

}

bool Engine::loadWorld(const string filename)
{
    try
    {
        log("Loading world from " + filename, 2);
        TiXmlDocument document(filename.c_str());
        int width = 0, height = 0;
        if (!xmlCheckDoc(&document)) throw "ERROR: wrong xml document!";
        TiXmlElement *root = document.RootElement();
        //Load World attributes
        log(root->Attribute("name"), 2);
        root->QueryIntAttribute("width", &width);
        root->QueryIntAttribute("height", &height);
        rooms_mgr->size(width, height);
        rooms_mgr->name(root->Attribute("name"));
        //TODO: manage different screen resolutions
        //Loading from xml
        std::vector <TiXmlElement *> images =
            xmlGetAllChilds(root->FirstChildElement("images"), "img");
        std::vector <TiXmlElement *> rooms =
            xmlGetAllChilds(root->FirstChildElement("rooms"), "room");
        std::vector <TiXmlElement *> events =
            xmlGetAllChilds(root->FirstChildElement("events"), "event");
        std::vector <TiXmlElement *> items =
            xmlGetAllChilds(root->FirstChildElement("items"), "item");
        std::vector <TiXmlElement *> vars =
            xmlGetAllChilds(root->FirstChildElement("vars"), "var");
        //Populating model
        createImgsFromXml(images);
        createEventsFromXml(events);
        createRoomsFromXml(rooms);
        createItemsFromXml(items);
        createVarsFromXml(vars);
        //TODO: load rest of world file
        string start_room = root->Attribute("start");
        apiRoomGoto(start_room);
        _state = GAME;
        return true;
    }
    catch (const char *msg)
    {
        log(msg, 1);
        return false;
    }
}

std::vector<std::pair<string, string> > Engine::getImgNames() const
{
    std::vector<std::pair<string, string> > v(images.begin(), images.end());
    return v;
}

void Engine::createImgsFromXml(std::vector <TiXmlElement *> imgs)
{
    for (std::vector<TiXmlElement *>::iterator i = imgs.begin();
         i != imgs.end(); ++i)
        images[(*i)->Attribute("id")] = (*i)->Attribute("file");
}

void Engine::createVarsFromXml(std::vector <TiXmlElement *> vars)
{
    for (std::vector<TiXmlElement *>::iterator i = vars.begin();
         i != vars.end(); ++i)
    {
        int var_value;
        (*i)->QueryIntAttribute("value", &var_value);
        events_mgr->var((*i)->Attribute("id"), var_value);
    }
}

void Engine::createEventsFromXml(std::vector <TiXmlElement *> events)
{
    for (std::vector<TiXmlElement *>::iterator i = events.begin();
         i != events.end(); ++i)
    {
        Event *event = events_mgr->addEvent((*i)->Attribute("id"));
        if (event == 0)
        {
            log("WARNING: cannot creating a new event!", 2);
            continue;
        }
        //create items parameters
        std::vector <TiXmlElement *> ireqs =
            xmlGetAllChilds((*i)->FirstChildElement("requirements"), "item_req");
        for (std::vector<TiXmlElement *>::iterator j = ireqs.begin();
             j != ireqs.end(); ++j)
            event->addItemReq((*j)->Attribute("id"), (*j)->Attribute("value"));
        //create var parameters
        std::vector <TiXmlElement *> vreqs =
            xmlGetAllChilds((*i)->FirstChildElement("requirements"), "var_req");
        for (std::vector<TiXmlElement *>::iterator j = vreqs.begin();
             j != vreqs.end(); ++j)
        {
            int var_value;
            (*j)->QueryIntAttribute("value", &var_value);
            event->addVarReq((*j)->Attribute("id"), var_value);
        }
        //create actions
        std::vector <TiXmlElement *> actions =
            xmlGetAllChilds((*i)->FirstChildElement("actions_if"), "action");
        for (std::vector<TiXmlElement *>::iterator j = actions.begin();
             j != actions.end(); ++j)
        {
            Action *act = event->addAction((*j)->Attribute("id"));
            if (act == 0)
            {
                log("WARNING: cannot create a new action!", 2);
                continue;
            }
            std::vector <TiXmlElement *> params =
                xmlGetAllChilds(*j, "param");
            for (std::vector<TiXmlElement *>::iterator z = params.begin();
                 z != params.end(); ++z)
                act->pushParam((*z)->Attribute("value"));
        }
    }
}

void Engine::createRoomsFromXml(std::vector <TiXmlElement *> rooms)
{
    for (std::vector<TiXmlElement *>::iterator i = rooms.begin();
         i != rooms.end(); ++i)
    {
        if (rooms_mgr->addRoom((*i)->Attribute("id"), (*i)->Attribute("bg")) == 0)
        {
            log("WARNING: cannot create a new room!", 2);
            continue;
        }
        std::vector <TiXmlElement *> areas =
            xmlGetAllChilds((*i)->FirstChildElement("areas"), "area");
        for (std::vector<TiXmlElement *>::iterator j = areas.begin();
             j != areas.end(); ++j)
        {
            int area_x, area_y, area_w, area_h, area_enab;
            (*j)->QueryIntAttribute("x", &area_x);
            (*j)->QueryIntAttribute("y", &area_y);
            (*j)->QueryIntAttribute("width", &area_w);
            (*j)->QueryIntAttribute("height", &area_h);
            Area * a = rooms_mgr->addArea((*j)->Attribute("id"),
                                (*i)->Attribute("id"),
                                area_x, area_y, area_w, area_h,
                                (*j)->FirstChildElement("do_event")->Attribute("value"));
            if (a == 0)
                log("WARNING: cannot create new area!", 2);
            else
            {
                (*j)->QueryIntAttribute("enabled", &area_enab);
                a->enabled(area_enab);
            }
        }
    }
}

void Engine::createItemsFromXml(std::vector <TiXmlElement *> items)
{
    for (std::vector<TiXmlElement *>::iterator i = items.begin();
         i != items.end(); ++i)
    {
        int area_x, area_y, area_w, area_h;
        (*i)->QueryIntAttribute("x", &area_x);
        (*i)->QueryIntAttribute("y", &area_y);
        (*i)->QueryIntAttribute("width", &area_w);
        (*i)->QueryIntAttribute("height", &area_h);
        if (rooms_mgr->addItem((*i)->Attribute("id"),
                            (*i)->Attribute("room"),
                            area_x, area_y, area_w, area_h,
                            (*i)->FirstChildElement("do_event")->Attribute("value"),
                            (*i)->Attribute("image")) == 0)
            log("WARNING: cannot create a new item!", 2);
    }
}

RoomsManager *Engine::getRoomsManager() const
{
    return rooms_mgr;
}

EventsManager *Engine::getEventsManager() const
{
    return events_mgr;
}

void Engine::execActions(std::vector <Action *> actions)
{
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); ++i)
    {
        //TODO: think about improving this loop
        Action act = *(*i);
        log("Exec action: " + act.id, 3);
        if (act.id == "ROOM_GOTO")
        {
            apiRoomGoto(act.popStrParam());
        } else if (act.id == "VAR_SET")
        {
            int var_value = act.popIntParam();
            string var_name = act.popStrParam();
            apiVarSet(var_name, var_value);
        } else if (act.id == "ITEM_MOVE")
        {
            string item_dest = act.popStrParam();
            string item_id = act.popStrParam();
            apiItemMove(item_id, item_dest);
        } else if (act.id == "AREA_SET_ENABLE")
        {
            int area_val = act.popIntParam();
            string area_id = act.popStrParam();
            apiAreaSetEnable(area_id, area_val);
        }
    }
}

void Engine::log(const string text, const int level)
{
    if (level <= DEBUG_LEVEL)
    {
        std::ofstream log_file;
        log_file.open("rooms.log", std::ios::out | std::ios::app);
        log_file << time(0) << ": " << text << '\n';
        log_file.close();
    }
}

void Engine::apiRoomGoto(const string id)
{
    log("ROOM_GOTO: " + id, 2);
    rooms_mgr->currentRoom(id);
}

void Engine::apiVarSet(const string id, const int value)
{
    log("VAR_SET: " + id, 2);
    events_mgr->var(id, value);
}

void Engine::apiItemMove(const string id, const string dest)
{
    log("ITEM_MOVE: " + id + ", dest: " + dest, 2);
    rooms_mgr->moveItem(id, dest);
}

void Engine::apiAreaSetEnable(const string id, const int value)
{
    bool bool_val = value;
    string str_val;
    bool_val ? str_val = "true" : str_val = "false";
    log("AREA_SET_ENABLE: " + id + ", enabled: " + str_val, 2);
    rooms_mgr->area(id)->enabled(bool_val);
}


