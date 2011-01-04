#include "engine.h"

Log logger;

const string Engine::VERSION = "ROOMS_VANILLA";

Engine::Engine()
{
    try
    {
        logger.write("\n* --------------\n* Engine version: " + VERSION +
                     "\n* --------------", Log::NOTE);
        rooms_mgr = new RoomsManager();
        events_mgr = new EventsManager();
        _state = INITIALIZING;
    }
    catch (...)
    {
        logger.write("ERROR: cannot create a valid engine!", Log::ERROR);
    }
}

Engine::~Engine()
{
    logger.write("QUITTING ENGINE", Log::ERROR);
    for (std::map<string, Dialog *>::iterator i = dialogs.begin();
         i != dialogs.end(); ++i)
    {
        logger.write("Garbage collector: " + i->second->id, Log::NOTE);
        delete i->second;
    }
    dialogs.clear();
    delete rooms_mgr;
    delete events_mgr;
}

Log *Engine::getLogger()
{
    return &logger;
}

std::pair<float, float> Engine::absToRelCoord(const int x, const int y)
{
    return std::make_pair(static_cast<float>(x) / rooms_mgr->width(), static_cast<float>(y) / rooms_mgr->height());
}

std::pair<int, int> Engine::relToAbsCoord(const float x, const float y)
{
    return std::make_pair(x * rooms_mgr->width(), y * rooms_mgr->height());
}

void Engine::clickArea(const float x, const float y)
{
    logger.write("Mouse click received", Log::NOTE);
    Event *event = events_mgr->event(rooms_mgr->eventAt(x, y));
    if (event == 0)
        return;
    logger.write("Event: " + event->id, Log::NOTE);
    if (rooms_mgr->checkItemPlace(event->itemReqs()) &&
        events_mgr->checkVarReqs(event->varReqs()))
        execActions(events_mgr->actionsForEvent(event->id));
    else
        logger.write("Requirements are not satisfied", Log::NOTE);
}

void Engine::clickDialog(const string link)
{
    logger.write("Dialog choice received: " + link, Log::NOTE);
    if (link == "-1")
    {
        setState(GAME);
        return;
    }
    execActions(dialog->jump(link));
}

Engine::State Engine::state() const
{
    return _state;
}

void Engine::setState(const Engine::State state_name)
{
    _state = state_name;
}

void Engine::loadGame(const string filename)
{

}

bool Engine::loadWorldFromFile(const string filename)
{
    logger.write("Loading world from: " + filename, Log::NOTE);
    std::ifstream xml(filename.c_str(), std::ios::binary);
    xml.seekg (0, std::ios::end);
    long length = xml.tellg();
    char *buffer = new char [length];
    xml.seekg (0, std::ios::beg);
    xml.read(buffer, length);
    bool res = loadWorldFromStr(buffer);
    xml.close();
    delete [] buffer;
    return res;
}

bool Engine::loadWorldFromStr(const string content)
{
    try
    {
        TiXmlDocument document;
        document.Parse(content.c_str());
        if (!xml::xmlCheckDoc(&document, Engine::VERSION)) throw "ERROR: wrong xml document!";
        TiXmlElement *root = document.RootElement();
        //Load World attributes
        logger.write(root->Attribute("name"), Log::NOTE);
        rooms_mgr->size(xml::xmlReadInt(root, "width"),
                        xml::xmlReadInt(root, "height"));
        rooms_mgr->name(root->Attribute("name"));
        //TODO: manage different screen resolutions
        //Loading from xml
        XmlVect images =
            xml::xmlGetAllChilds(root->FirstChildElement("images"), "img");
        XmlVect rooms =
            xml::xmlGetAllChilds(root->FirstChildElement("rooms"), "room");
        XmlVect events =
            xml::xmlGetAllChilds(root->FirstChildElement("events"), "event");
        XmlVect items =
            xml::xmlGetAllChilds(root->FirstChildElement("items"), "item");
        XmlVect vars =
            xml::xmlGetAllChilds(root->FirstChildElement("vars"), "var");
        XmlVect diags =
            xml::xmlGetAllChilds(root->FirstChildElement("dialogs"), "dialog");
        //Populating model
        createImgsFromXml(images);
        createEventsFromXml(events);
        createRoomsFromXml(rooms);
        createItemsFromXml(items);
        createVarsFromXml(vars);
        createDialogsFromXml(diags);
        //TODO: load rest of world file
        string start_room = root->Attribute("start");
        apiRoomGoto(start_room);
        _state = GAME;
        return true;
    }
    catch (const char *msg)
    {
        logger.write(msg, Log::ERROR);
        return false;
    }
}

std::vector<string> Engine::getImgNames() const
{
    return images;
}

std::vector<Item *> Engine::getInventory() const
{
    return rooms_mgr->room(ROOM_INV)->items();
}

void Engine::createImgsFromXml(XmlVect imgs)
{
    for (XmlVect::iterator i = imgs.begin();
         i != imgs.end(); ++i)
        images.push_back((*i)->Attribute("file"));
}

void Engine::createVarsFromXml(XmlVect vars)
{
    for (XmlVect::iterator i = vars.begin();
         i != vars.end(); ++i)
        events_mgr->setVar((*i)->Attribute("id"), xml::xmlReadInt((*i), "value"));
}

void Engine::fillEventFromXml(TiXmlElement *elem, Event *event)
{
    //create items parameters
    XmlVect ireqs = xml::xmlGetAllChilds(elem->FirstChildElement("requirements"), "item_req");
    for (XmlVect::iterator j = ireqs.begin(); j != ireqs.end(); ++j)
        event->addItemReq((*j)->Attribute("id"), (*j)->Attribute("value"));
    //create var parameters
    XmlVect vreqs = xml::xmlGetAllChilds(elem->FirstChildElement("requirements"), "var_req");
    for (XmlVect::iterator j = vreqs.begin(); j != vreqs.end(); ++j)
        event->addVarReq((*j)->Attribute("id"), xml::xmlReadInt((*j), "value"));
    //create actions
    XmlVect actions = xml::xmlGetAllChilds(elem->FirstChildElement("actions_if"), "action");
    for (XmlVect::iterator j = actions.begin(); j != actions.end(); ++j)
    {
        Action *act = event->addAction((*j)->Attribute("id"));
        XmlVect params = xml::xmlGetAllChilds(*j, "param");
        for (XmlVect::iterator z = params.begin(); z != params.end(); ++z)
            act->pushParam((*z)->Attribute("value"));
    }
}

void Engine::createEventsFromXml(XmlVect events)
{
    for (XmlVect::iterator i = events.begin(); i != events.end(); ++i)
        fillEventFromXml(*i, events_mgr->addEvent((*i)->Attribute("id")));
}

void Engine::createRoomsFromXml(XmlVect rooms)
{
    for (XmlVect::iterator i = rooms.begin(); i != rooms.end(); ++i)
    {
        rooms_mgr->addRoom((*i)->Attribute("id"), (*i)->Attribute("bg"));
        XmlVect areas = xml::xmlGetAllChilds((*i)->FirstChildElement("areas"), "area");
        for (XmlVect::iterator j = areas.begin(); j != areas.end(); ++j)
        {
            rooms_mgr->addArea((*j)->Attribute("id"),
                               (*i)->Attribute("id"),
                               xml::xmlReadFloat((*j), "x"),
                               xml::xmlReadFloat((*j), "y"),
                               xml::xmlReadFloat((*j), "width"),
                               xml::xmlReadFloat((*j), "height"),
                               (*j)->FirstChildElement("do_event")->Attribute("value"));
        }
    }
}

void Engine::createItemsFromXml(XmlVect items)
{
    for (XmlVect::iterator i = items.begin(); i != items.end(); ++i)
    {
        rooms_mgr->addItem((*i)->Attribute("id"),
                            (*i)->Attribute("room"),
                            xml::xmlReadFloat((*i), "x"),
                            xml::xmlReadFloat((*i), "y"),
                            xml::xmlReadFloat((*i), "width"),
                            xml::xmlReadFloat((*i), "height"),
                            (*i)->FirstChildElement("do_event")->Attribute("value"),
                            (*i)->Attribute("image"));
    }
}

void Engine::createDialogsFromXml(XmlVect diags)
{
    for (XmlVect::iterator i = diags.begin(); i != diags.end(); ++i)
    {
        Dialog *d = new Dialog((*i)->Attribute("id"), (*i)->Attribute("start"));
        dialogs[d->id] = d;
        XmlVect steps = xml::xmlGetAllChilds((*i), "step");
        for (XmlVect::iterator j = steps.begin(); j != steps.end(); ++j)
        {
            DialogStep *step = d->addStep((*j)->Attribute("id"), (*j)->Attribute("text"));
            fillEventFromXml(*j, step->event);
            XmlVect links = xml::xmlGetAllChilds((*j), "link");
            for (XmlVect::iterator z = links.begin(); z != links.end(); ++z)
            {
                d->addLink(step->id, (*z)->Attribute("id"), (*z)->Attribute("text"));
            }
        }
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

string Engine::getDialogText()
{
    return dialog->text();
}
std::map<string, string> Engine::getDialogChoices()
{
    std::map<string, string> choices;
    std::vector< std::pair<string, string> > links = dialog->links();
    for (std::vector< std::pair<string, string> >::iterator i = links.begin();
         i != links.end(); ++i)
    {
        DialogStep *step = dialog->step(i->first);
        if (step == 0) //its an end-of-dialog link
            choices[i->second] = i->first;
        else if (rooms_mgr->checkItemPlace(step->event->itemReqs()) &&
            events_mgr->checkVarReqs(step->event->varReqs()))
            choices[i->second] = i->first;
    }
    return choices;
}

void Engine::execActions(std::vector <Action *> actions)
{
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); ++i)
    {
        //TODO: think about improving this loop
        Action act = *(*i);
        logger.write("Exec action: " + act.id, Log::NOTE);
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
        } else if (act.id == "DIALOG_START")
        {
            string diag_id = act.popStrParam();
            apiDialogStart(diag_id);
        }
    }
}

void Engine::apiRoomGoto(const string id)
{
    logger.write("ROOM_GOTO: " + id, Log::NOTE);
    rooms_mgr->setCurrentRoom(id);
}

void Engine::apiVarSet(const string id, const int value)
{
    logger.write("VAR_SET: " + id, Log::NOTE);
    events_mgr->setVar(id, value);
}

void Engine::apiItemMove(const string id, const string dest)
{
    logger.write("ITEM_MOVE: " + id + ", dest: " + dest, Log::NOTE);
    rooms_mgr->moveItem(id, dest);
}

void Engine::apiDialogStart(const string id)
{
    logger.write("DIALOG_START: " + id, Log::NOTE);
    dialog = dialogs[id];
    dialog->reset();
    setState(DIALOG);
    execActions(dialog->actions());
}

