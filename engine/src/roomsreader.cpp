#include "roomsreader.h"

RRNode::RRNode(TiXmlElement *root)
{
    this->root = root;
    parent = 0;
    gotoRoot();
}

RRNode::~RRNode()
{

}

RRNode *RRNode::gotoElement(string name)
{
    cursor = findElement(root, name);
    if (!isNull())
        parent = cursor->Parent()->ToElement();
    else
        parent = 0;
    return this;
}

RRNode *RRNode::gotoRoot()
{
    cursor = root;
    parent = 0;
    return this;
}

RRNode *RRNode::gotoChild(string name)
{
    if(!isNull())
    {
        parent = cursor;
        cursor = cursor->FirstChildElement(name.c_str());
    }
    return this;
}

RRNode *RRNode::gotoParent()
{
    cursor = parent;
    if(!isNull())
    {
        parent = cursor->Parent()->ToElement();
    }
    return this;
}

RRNode *RRNode::gotoNext()
{
    if(!isNull())
        cursor = cursor->NextSiblingElement(cursor->Value());
    return this;
}

RRNode *RRNode::appendElement(string name)
{
    if(!isNull())
    {
        TiXmlElement *new_elem = new TiXmlElement(name.c_str());
        cursor->LinkEndChild(new_elem);
        parent = cursor;
        cursor = new_elem;
    }
    return this;
}

bool RRNode::isNull()
{
    bool result = cursor;
    return !result;
}

int RRNode::attrInt(string name)
{
    int tmp = 0;
    cursor->QueryIntAttribute(name.c_str(), &tmp);
    return tmp;
}

float RRNode::attrFloat(string name)
{
    float tmp = 0.0;
    cursor->QueryFloatAttribute(name.c_str(), &tmp);
    return tmp;
}

string RRNode::attrStr(string name)
{
    return cursor->Attribute(name.c_str());
}

void RRNode::setAttr(string name, string value)
{
    cursor->SetAttribute(name.c_str(), value.c_str());
}

Event *RRNode::fetchEvent()
{
    if (isNull()) return 0;
    Event *event = new Event(attrStr("id"));
    for (gotoChild("item_req"); !isNull(); gotoNext())
        event->addItemReq(attrStr("id"), attrStr("value"));
    gotoParent();
    for (gotoChild("var_req"); !isNull(); gotoNext())
        event->addVarReq(attrStr("id"), attrInt("value"));
    gotoParent();
    for (gotoChild("action"); !isNull(); gotoNext())
    {
        Action *act = event->addAction(attrStr("id"));
        for (gotoChild("param"); !isNull(); gotoNext())
            act->pushParam(attrStr("value"));
        gotoParent();
        gotoChild("animations");
        if (!isNull()){
            for (gotoChild("animation"); !isNull(); gotoNext()){
                fetchAnimation();//TODO: do something with animation
            }
            gotoParent();
        }
        gotoParent();
    }
    gotoParent();
    return event;
}

Room *RRNode::fetchRoom()
{
    if (isNull()) return 0;
    Room *room = new Room(attrStr("id"));
    room->setBg(attrStr("bg"));
    room->setBgm(attrStr("bgm"));
    for (gotoChild("area"); !isNull(); gotoNext())
    {
        Area *area = room->addArea(attrStr("id"));
        area->setSize(attrFloat("x"), attrFloat("y"), attrFloat("width"), attrFloat("height"));
        area->setEvent(attrStr("event"));
    }
    gotoParent();
    return room;
}

Item *RRNode::fetchItem()
{
    if (isNull()) return 0;
    Item *item = new Item(attrStr("id"));
    item->setSize(attrFloat("x"), attrFloat("y"), attrFloat("width"), attrFloat("height"));
    item->setEvent(attrStr("event"));
    item->setImage(attrStr("image"));
    item->move(attrStr("room"));
    return item;
}

Dialog *RRNode::fetchDialog()
{
    if (isNull()) return 0;
    Dialog *d = new Dialog(attrStr("id"), attrStr("start"));
    for (gotoChild("step"); !isNull(); gotoNext())
    {
        DialogStep *step = d->addStep(attrStr("id"), attrStr("text"));
        step->event = fetchEvent();
        for (gotoChild("link"); !isNull(); gotoNext())
            d->addLink(step->id, attrStr("id"), attrStr("text"));
         gotoParent();

    }
    gotoParent();
    return d;
}

Animation *RRNode::fetchAnimation()
{
    Animation *a = new Animation(attrStr("object"), attrInt("duration"));
    a->setEasing(Animation::strToEasing(attrStr("easing")));
    for (gotoChild("property"); !isNull(); gotoNext())
        a->addProperty(attrStr("name"), attrFloat("from"), attrFloat("to"));
    gotoParent();
    return a;
}

TiXmlElement *RRNode::findElement(TiXmlElement *elem, string name)
{
    if (elem == 0)
        return 0;
    if (string(elem->Value()) == name)
        return elem;
    TiXmlElement *result = findElement(elem->NextSiblingElement(), name);
    if (result != 0)
        return result;
    result = findElement(elem->FirstChildElement(), name);
    if (result != 0)
        return result;
    return 0;
}


string floatToStr(const float f)
{
    std::ostringstream os;
    os << f;
    return os.str();
}

RoomsReader::RoomsReader()
{
    crawler = 0;
    doc = 0;
    file_version = 0;
    parse_map["world"] = &RoomsReader::parseWorld;
    parse_map["room"] = &RoomsReader::parseRoom;
    parse_map["area"] = &RoomsReader::parseArea;
    parse_map["action"] = &RoomsReader::parseAction;
    parse_map["event"] = &RoomsReader::parseEvent;
    parse_map["animation"] = &RoomsReader::parseAnimation;
    parse_map["property"] = &RoomsReader::parseProperty;
    parse_map["dialog"] = &RoomsReader::parseDialog;
    parse_map["step"] = &RoomsReader::parseDialogStep;
    parse_map["var"] = &RoomsReader::parseVar;
    parse_map["item"] = &RoomsReader::parseItem;
    parse_map["param"] = &RoomsReader::parseParam;
    parse_map["item_req"] = &RoomsReader::parseItemReq;
    parse_map["var_req"] = &RoomsReader::parseVarReq;
    parse_map["img"] = &RoomsReader::parseImages;
}

RoomsReader::~RoomsReader()
{
    if(crawler)
        delete crawler;
    if (doc)
        delete doc;
}

bool RoomsReader::loadFromFile(const string filename)
{
    std::ifstream xml(filename.c_str(), std::ios::binary);
    if (!xml.good()) return false;
    xml.seekg (0, std::ios::end);
    long length = xml.tellg();
    if (length == 0) return false;
    char *buffer = new char [length];
    xml.seekg (0, std::ios::beg);
    xml.read(buffer, length);
    bool res = loadFromStr(buffer);
    xml.close();
    delete [] buffer;
    return res;
}

bool RoomsReader::loadFromStr(const string content)
{
    doc = new TiXmlDocument;
    doc->Parse(content.c_str());
    crawler = new RRNode(doc->RootElement());
    file_content = content;
    return true;
}

void RoomsReader::loadEmptyDoc()
{
    doc = new TiXmlDocument;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
    TiXmlElement *element = new TiXmlElement("world");
    doc->LinkEndChild(decl);
    doc->LinkEndChild(element);
    crawler = new RRNode(doc->RootElement());
}

void RoomsReader::saveDoc(string filename)
{
    if (!doc->SaveFile(filename.c_str()))
        logger.write("Cannot save to " + filename, Log::ERROR);
}

bool RoomsReader::parse()
{
    bool pr;

    // Figure out the project version
    pr = parseWorld(doc->RootElement());

    // The project version couldn't be retrieved, something wrong happened
    if (!pr || file_version == 0)
        return false;

    // At this point, file_version is set as a side effect, so it's possible to
    // know whether we need to upgrade the document to the latest Rooms version.

    if (file_version < Versioning::VERSION)
    {
        logger.write("Old version detected: " + floatToStr(file_version) + ". Upgrading...", Log::WARNING);
        string new_content = Versioning::upgrade(file_version, file_content);

        // Sets file_content as side effect
        loadFromStr(new_content);
    }

    // Recursively parse the whole document
    pr = parseElement(doc->RootElement());
    if (!pr)
    {
        // There were some errors during parsing
        delete doc;
        doc = 0;
        return false;
    }

    return true;
}

RRNode *RoomsReader::getCrawler()
{
    return crawler;
}

bool RoomsReader::checkUniqueId(std::set<string> &ids, const string id)
{
    if (ids.count(id) != 0)
        return false;
    ids.insert(id);
    return true;
}

bool RoomsReader::checkParent(TiXmlElement *elem, string name)
{
    return (elem->Parent() != 0 &&
            string(elem->Parent()->Value()) == name);
}

bool RoomsReader::parseElement(TiXmlElement *elem)
{
    if (elem == 0)
        return true;
    bool value = true;
    if (parse_map.find(elem->Value()) != parse_map.end())
    {
        ParseMethod method = parse_map.find(elem->Value())->second;
        value = (this->*method)(elem);
    }
    return (value && parseElement(elem->FirstChildElement()) && parseElement(elem->NextSiblingElement()));
}

bool RoomsReader::parseArea(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "x", ATTR_FLOAT) &&
          parseAttr(elem, "y", ATTR_FLOAT) &&
          parseAttr(elem, "width", ATTR_FLOAT) &&
          parseAttr(elem, "height", ATTR_FLOAT)))
        return false;
    if (!(checkUniqueId(unique_ids_areas, elem->Attribute("id")) &&
        checkParent(elem, "room")))
        return false;
    return true;
}

bool RoomsReader::parseItem(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "room", ATTR_STR) &&
          parseAttr(elem, "image", ATTR_STR) &&
          parseAttr(elem, "x", ATTR_FLOAT) &&
          parseAttr(elem, "y", ATTR_FLOAT) &&
          parseAttr(elem, "width", ATTR_FLOAT) &&
          parseAttr(elem, "height", ATTR_FLOAT)))
        return false;
    if (!(checkUniqueId(unique_ids_items, elem->Attribute("id")) &&
        checkParent(elem, "items") &&
        !checkUniqueId(unique_ids_images, elem->Attribute("image"))))
        return false;
    return true;
}

bool RoomsReader::parseRoom(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "bg", ATTR_STR)))
        return false;
    if (!(checkUniqueId(unique_ids_rooms, elem->Attribute("id")) &&
          checkParent(elem, "rooms")))
        return false;
    return true;
}

bool RoomsReader::parseAction(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
         (checkParent(elem, "event") || checkParent(elem, "step"))))
        return false;
    return true;
}

bool RoomsReader::parseWorld(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "version", ATTR_INT) &&
          parseAttr(elem, "name", ATTR_STR) &&
          parseAttr(elem, "start", ATTR_STR) &&
          parseAttr(elem, "width", ATTR_INT) &&
          parseAttr(elem, "height", ATTR_INT)))
        return false;
    elem->QueryIntAttribute("version", &file_version);
    return true;
}

bool RoomsReader::parseEvent(TiXmlElement *elem)
{
    if (!parseAttr(elem, "id", ATTR_STR))
        return false;
    if (!(checkUniqueId(unique_ids_events, elem->Attribute("id")) &&
        checkParent(elem, "events")))
        return false;
    return true;
}

bool RoomsReader::parseAnimation(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "object", ATTR_STR) &&
          parseAttr(elem, "duration", ATTR_INT) &&
          parseAttr(elem, "easing", ATTR_STR)))
        return false;
    if (!checkParent(elem, "animations"))
        return false;
    return true;
}

bool RoomsReader::parseProperty(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "name", ATTR_STR) &&
          parseAttr(elem, "from", ATTR_FLOAT) &&
          parseAttr(elem, "to", ATTR_FLOAT)))
        return false;
    if (!checkParent(elem, "animation"))
        return false;
    return true;
}

bool RoomsReader::parseVar(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "value", ATTR_STR) &&
          checkParent(elem, "vars")))
        return false;
    return true;
}

bool RoomsReader::parseImages(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "file", ATTR_STR) &&
        checkParent(elem, "images")))
        return false;
    if (!checkUniqueId(unique_ids_images, elem->Attribute("file")))
        return false;
    return true;
}


bool RoomsReader::parseItemReq(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "value", ATTR_STR)))
        return false;
    if (!(!checkUniqueId(unique_ids_items, elem->Attribute("id")) &&
        (checkParent(elem, "event") || checkParent(elem, "step"))))
        return false;
    return true;
}

bool RoomsReader::parseVarReq(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "value", ATTR_INT)))
        return false;
    if (!(checkParent(elem, "event") || checkParent(elem, "step")))
        return false;
    return true;
}

bool RoomsReader::parseParam(TiXmlElement *elem)
{
    if (!parseAttr(elem, "value", ATTR_STR))
        return false;
    return true;
}

bool RoomsReader::parseDialog(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "start", ATTR_STR)))
        return false;
    if (!(checkUniqueId(unique_ids_dialogs, elem->Attribute("id")) &&
        checkParent(elem, "dialogs")))
        return false;
    return true;
}

bool RoomsReader::parseDialogStep(TiXmlElement *elem)
{
    if (!(parseAttr(elem, "id", ATTR_STR) &&
          parseAttr(elem, "text", ATTR_STR) &&
          checkParent(elem, "dialog")))
        return false;
    return true;
}

bool RoomsReader::parseAttr(TiXmlElement *elem, string name, AttributeType type)
{
    switch (type)
    {
        case ATTR_FLOAT:
        {
            float tmp;
            return (elem->QueryFloatAttribute(name.c_str(), &tmp) == TIXML_SUCCESS);
            break;
        }
        case ATTR_INT:
        {
            int tmp;
            return (elem->QueryIntAttribute(name.c_str(), &tmp) == TIXML_SUCCESS);
            break;
        }
        case ATTR_STR:
        {
            return (elem->Attribute(name.c_str()));
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}
