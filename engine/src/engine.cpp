#include "engine.h"
#include "csparser.h"

Log logger;

Engine::Engine()
{
    rooms_mgr = new RoomsManager();
    events_mgr = new EventsManager();
    gui_mgr = new GuiManager();
    anim_mgr = new AnimationsManager();
    cs_mgr = new CsManager();
    setState(INITIALIZING);
    inventory = new GuiScrolledBar("inventory", "", "", GuiRect(0.08, 0, 0.84, 0.107),
                                GuiRect(0.08, 0, 0.08, 0.107), GuiRect(0, 0, 0.08, 0.107),
                                "./data/right_btn.png", "./data/left_btn.png", GuiList::H_GUILIST);
    dialog_list = new GuiScrolledBar("dialog", "", "", GuiRect(0.08, 0.89, 0.84, 0.107),
                                    GuiRect(0.08, 0.89, 0.65, 0.05), GuiRect(0, 0, 0.08, 0.107),
                                    "./data/right_btn.png", "./data/left_btn.png", GuiList::V_GUILIST);
    gui_mgr->addGuiObj(inventory);
    gui_mgr->addGuiObj(dialog_list);
    dialog_list->visible = false;
    stored_state = state();
#ifdef WITH_PYTHON
    // Python stuff
    apiInit(this);
    EngineMod eng_mod;
    RoomMod room_mod;
    vm.import(eng_mod);
    vm.import(room_mod);
#endif
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
    delete gui_mgr;
}

Log *Engine::getLogger()
{
    return &logger;
}

std::pair<float, float> Engine::absToRelCoord(const int x, const int y)
{
    return std::make_pair(static_cast<float> (x) / rooms_mgr->width(), static_cast<float> (y) / rooms_mgr->height());
}

std::pair<int, int> Engine::relToAbsCoord(const float x, const float y)
{
    return std::make_pair(x * rooms_mgr->width(), y * rooms_mgr->height());
}

void Engine::relToAbsRect(GuiRect &rect)
{
    rect.x *= rooms_mgr->width();
    rect.w *= rooms_mgr->width();
    rect.y *= rooms_mgr->height();
    rect.h *= rooms_mgr->height();
}

void Engine::click(const float x, const float y)
{
    switch (state())
    {
        case GAME:
        {
            if (gui_mgr->click(x, y) == "")
                clickArea(x, y);
            break;
        }
        case DIALOG:
        {
            string choice = gui_mgr->click(x, y);
            if (choice != "")
            {
                clickDialog(choice);
                updateDialog();
            }
            break;
        }
        case TRANSITION:
        case CUTSCENE:
        {
            // do nothing when an animation is running
            break;
        }
        default:
            gui_mgr->click(x, y);
    }
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
    std::map<string, string> choices = getDialogChoices();
    string id_step = choices[link];
    if (id_step == "-1")
    {
        setState(GAME);
        return;
    }
    execActions(dialog->jump(id_step));
}

Engine::State Engine::state() const
{
    return _state;
}

void Engine::setState(const Engine::State state_name)
{
    _state = state_name;
}

void Engine::saveGame(const string filename)
{
    logger.write("Saving to file: " + filename, Log::NOTE);
    RoomsReader reader;
    reader.loadEmptyDoc();
    RRNode *node = reader.getCrawler();
    node->gotoElement("world");
    node->setAttr("version", floatToStr(Versioning::VERSION));
    node->setAttr("current_room", rooms_mgr->currentRoom()->id);
    node->appendElement("vars");
    std::map<string, int> vars = events_mgr->getVars();
    for (std::map<string, int>::iterator i = vars.begin();
            i != vars.end(); ++i)
    {
        node->appendElement("var");
        node->setAttr("id", i->first);
        node->setAttr("value", floatToStr(i->second));
        node->gotoParent();
    }
    node->gotoElement("world");
    node->appendElement("items");
    std::map<string, Item *> items = rooms_mgr->getItems();
    for (std::map<string, Item *>::iterator i = items.begin();
            i != items.end(); ++i)
    {
        node->appendElement("item");
        node->setAttr("id", i->first);
        node->setAttr("room", i->second->parent());
        node->gotoParent();
    }
    reader.saveDoc(filename);
}

void Engine::loadGame(const string filename)
{
    logger.write("Loading file: " + filename, Log::NOTE);
    RoomsReader reader;
    reader.loadFromFile(filename);
    RRNode *node = reader.getCrawler();
    for (node->gotoElement("items")->gotoChild("item"); !node->isNull(); node->gotoNext())
        rooms_mgr->moveItem(node->attrStr("id"), node->attrStr("room"));
    node->gotoRoot();

    for (node->gotoElement("vars")->gotoChild("var"); !node->isNull(); node->gotoNext())
        events_mgr->setVar(node->attrStr("id"), node->attrInt("value"));
    node->gotoRoot();
    apiRoomGoto(node->gotoElement("world")->attrStr("current_room"));
}

bool Engine::loadWorldFromFile(const string filename)
{
    logger.write("Loading world from: " + filename, Log::NOTE);
    std::ifstream xml(filename.c_str(), std::ios::binary);
    if (!xml.good()) return false;
    xml.seekg(0, std::ios::end);
    long length = xml.tellg();
    if (length == 0) return false;
    char *buffer = new char [length];
    xml.seekg(0, std::ios::beg);
    xml.read(buffer, length);
    bool res = loadWorldFromStr(buffer);
    xml.close();
    delete [] buffer;
    return res;
}

bool Engine::loadWorldFromStr(const string content)
{
    RoomsReader reader;
    if (!reader.loadFromStr(content) || !reader.parse())
    {
        logger.write("ERROR: wrong xml document!", Log::ERROR);
        return false;
    }
    RRNode *node = reader.getCrawler();
    node->gotoElement("world");
    string start_room = node->attrStr("start");
    //Load World attributes
    logger.write(node->attrStr("name"), Log::NOTE);
    rooms_mgr->setRoomSize(node->attrInt("width"), node->attrInt("height"));
    rooms_mgr->setWorldName(node->attrStr("name"));
    //Loading from xml
    for (node->gotoElement("images")->gotoChild("img"); !node->isNull(); node->gotoNext())
        images.push_back(node->attrStr("file"));
    node->gotoRoot();

    for (node->gotoElement("events")->gotoChild("event"); !node->isNull(); node->gotoNext())
        events_mgr->addEvent(node->fetchEvent());
    node->gotoRoot();

    for (node->gotoElement("rooms")->gotoChild("room"); !node->isNull(); node->gotoNext())
        rooms_mgr->addRoom(node->fetchRoom());
    node->gotoRoot();

    for (node->gotoElement("items")->gotoChild("item"); !node->isNull(); node->gotoNext())
        rooms_mgr->addItem(node->fetchItem());
    node->isNull();
    node->gotoRoot();

    for (node->gotoElement("vars")->gotoChild("var"); !node->isNull(); node->gotoNext())
        events_mgr->setVar(node->attrStr("id"), node->attrInt("value"));
    node->gotoRoot();

    for (node->gotoElement("dialogs")->gotoChild("dialog"); !node->isNull(); node->gotoNext())
        dialogs[node->attrStr("id")] = node->fetchDialog();
    node->gotoRoot();

    apiRoomGoto(start_room);
    setState(GAME);
    return true;
}

std::vector<string> Engine::getImgNames() const
{
    return images;
}

std::vector<Item *> Engine::getInventory() const
{
    return rooms_mgr->room(ROOM_INV)->items();
}

RoomsManager *Engine::getRoomsManager() const
{
    return rooms_mgr;
}

EventsManager *Engine::getEventsManager() const
{
    return events_mgr;
}

GuiManager *Engine::getGuiManager() const
{
    return gui_mgr;
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

std::vector<string> Engine::getSFX()
{
    std::vector<string> sfx_ = sfx;
    sfx.clear();
    return sfx_;
}

void Engine::execActions(std::vector <Action *> actions)
{
    std::vector <Action *>::iterator i;
    for (i = actions.begin(); i != actions.end(); ++i)
    {
        //TODO: think about improving this loop
        Action act = *(*i);
        anim_mgr->addAnimations(act.animations());
        logger.write("Exec action: " + act.id, Log::NOTE);
        if (act.id == "ROOM_GOTO")
        {
            apiRoomGoto(act.popStrParam());
        }
        else if (act.id == "VAR_SET")
        {
            int var_value = act.popIntParam();
            string var_name = act.popStrParam();
            apiVarSet(var_name, var_value);
        }
        else if (act.id == "ITEM_MOVE")
        {
            string item_dest = act.popStrParam();
            string item_id = act.popStrParam();
            apiItemMove(item_id, item_dest);
        }
        else if (act.id == "DIALOG_START")
        {
            string diag_id = act.popStrParam();
            apiDialogStart(diag_id);
        }
        else if (act.id == "SFX_PLAY")
        {
            string sfx_id = act.popStrParam();
            apiSFXPlay(sfx_id);
        }
        else if (act.id == "CUTSCENE_START")
        {
            apiStartCutScene(act.popStrParam());
        }
#ifdef WITH_PYTHON
        else if (act.id == "SCRIPT")
        {
            string sfx_id = act.popStrParam();
            apiExecScript(sfx_id);
        }
#endif
    }
}

void Engine::updateDialog()
{
    dialog_list->visible = false;
    dialog_list->clear();
    if (state() == DIALOG)
    {
        dialog_list->setCaption(getDialogText());
        std::map<string, string> choices = getDialogChoices();
        for (std::map<string, string>::iterator i = choices.begin();
                i != choices.end(); ++i)
        {
            dialog_list->addButton(i->first, i->first, "");
            logger.write(i->first, Log::NOTE);
        }
        dialog_list->visible = true;
    }
}

GuiDataVect Engine::flash(Room *room)
{
    // Background visible data
    GuiDataVect visible_data;
    GuiData bg;
    bg.id = room->id;
    bg.alpha = 1;
    bg.image = room->bg();
    bg.text = "";
    bg.rect = GuiRect(0, 0, 1.0, 1.0);
    if (state() == TRANSITION){
        Room * prev_bg = rooms_mgr->previousRoom();
        if (prev_bg != 0) {
            GuiData pbg;
            pbg.id = prev_bg->id;
            pbg.alpha = 0;
            pbg.image = prev_bg->bg();
            pbg.text = "";
            pbg.rect = GuiRect(0, 0, 1.0, 1.0);
            anim_mgr->updateObjectState(prev_bg->id, &pbg);
            visible_data.push_back(pbg);
        }
        anim_mgr->updateObjectState(room->id, &bg);
    }
    visible_data.push_back(bg);
    // Items visible data
    std::vector <Item *> items = room->items();
    for (std::vector<Item *>::iterator i = items.begin();
            i != items.end(); ++i)
    {
        GuiData item;
        item.id = (*i)->id;
        item.alpha = 1;
        item.text = "";
        item.image = (*i)->image();
        item.rect = GuiRect((*i)->x(), (*i)->y(), (*i)->w(), (*i)->h());
        if (state() == TRANSITION){
            anim_mgr->updateObjectState((*i)->id, &item);
            (*i)->setSize(item.rect.x, item.rect.y, item.rect.w, item.rect.h);
        }
        visible_data.push_back(item);
    }
    return visible_data;
}

GuiDataVect Engine::getCutsceneVisibleData()
{
    if (!anim_mgr->isAnimating()){
        anim_mgr->startAnimations();
    }
    if (anim_mgr->stopIfOvertime()){
        logger.write("Exiting cutscene", Log::NOTE);
        restoreState();
    }
    GuiDataVect visible_data = cs_mgr->getVisibleData();
    GuiDataVect::iterator i;
    for (i = visible_data.begin(); i != visible_data.end(); ++i){
        anim_mgr->updateObjectState((*i).id, &(*i));
    }
    cs_mgr->setVisibleData(visible_data);
    return visible_data;
}

GuiDataVect Engine::getVisibleData()
{
    if (state() == CUTSCENE){
        return getCutsceneVisibleData();
    }
    if (anim_mgr->hasAnimations() && state() != TRANSITION) {
        anim_mgr->startAnimations();
        storeState();
        setState(TRANSITION);
        logger.write("Entering transition", Log::NOTE);
    }
    if (state() == TRANSITION && anim_mgr->stopIfOvertime()){
        logger.write("Exiting transition", Log::NOTE);
        restoreState();
    }
    GuiDataVect visible_data;
    GuiDataVect gui_data = gui_mgr->getVisibleData();
    GuiDataVect room_data = flash(rooms_mgr->currentRoom());

    visible_data.insert(visible_data.end(), room_data.begin(), room_data.end());
    visible_data.insert(visible_data.end(), gui_data.begin(), gui_data.end());

    return visible_data;
}

void Engine::storeState()
{
    stored_state = state();
}

void Engine::restoreState()
{
    setState(stored_state);
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
    Item * item = rooms_mgr->item(id);
    string source = item->parent();
    rooms_mgr->moveItem(id, dest);
    if (source == "!INVENTORY")
        inventory->remButton(id);
    if (dest == "!INVENTORY")
        inventory->addButton(id, "", item->image());
}

void Engine::apiDialogStart(const string id)
{
    logger.write("DIALOG_START: " + id, Log::NOTE);
    dialog = dialogs[id];
    dialog->reset();
    setState(DIALOG);
    updateDialog();
    execActions(dialog->actions());
}

void Engine::apiSFXPlay(const string id)
{
    sfx.push_back(id);
}

void Engine::apiStartCutScene(const std::string scenefile)
{
    if (cs_mgr->startCutscene(scenefile, images)){
        //TODO: transizioni e cutscene non vanno daccordo
        storeState();
        setState(CUTSCENE);
        logger.write("Entering cutscene", Log::NOTE);
        std::vector<SequentialAnimation *> anims = cs_mgr->getAnimations();
        std::vector<SequentialAnimation *>::iterator i;
        for (i = anims.begin(); i != anims.end(); ++i){
            anim_mgr->addSequentialAnimation(*i);
        }
    }
}

#ifdef WITH_PYTHON
void Engine::apiExecScript(const string id)
{
    vm.execute(id);
}
#endif

