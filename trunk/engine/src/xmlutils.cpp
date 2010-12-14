#include "xmlutils.h"

bool xmlCheckDoc(TiXmlDocument *doc)
{
    if (doc)
        return doc->LoadFile() &&
               xmlCheckRoot(doc->RootElement()) &&
               xmlCheckImages(doc->RootElement()->FirstChildElement("images")) &&
               xmlCheckEvents(doc->RootElement()->FirstChildElement("events")) &&
               xmlCheckRooms(doc->RootElement()->FirstChildElement("rooms")) &&
               xmlCheckRooms(doc->RootElement()->FirstChildElement("items"));
    return false;
}

bool xmlCheckRoot(TiXmlElement *elem)
{
    int tmp;
    if (!elem)
        return false;
    std::string name = elem->Value();
    if (name != "world" ||
        elem->Attribute("name") == 0 ||
        elem->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
        elem->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
        elem->Attribute("version") == 0 ||
        elem->Attribute("start") == 0)
        return false;
    return true;
}

bool xmlCheckImages(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("img"); i != 0;
             i = i->NextSiblingElement("img"))
        {
            if (i->Attribute("id") == 0 ||
                i->Attribute("file") == 0)
                return false;
        }
    return true;
}

bool xmlCheckEvents(TiXmlElement *elem)
{
    if (elem)
    {
        for (TiXmlElement *i = elem->FirstChildElement("event"); i != 0;
             i = i->NextSiblingElement("event"))
        {
            if (i->Attribute("id") == 0 ||
                !xmlCheckActions(i->FirstChildElement("actions_if")))
                return false;
        }
    }
    return true;
}

bool xmlCheckActions(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("action"); i != 0;
             i = i->NextSiblingElement("action"))
        {
            if (i->Attribute("id") == 0 || !xmlCheckParams(i))
                return false;
        }
    return true;
}

bool xmlCheckParams(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("param"); i != 0;
             i = i->NextSiblingElement("param"))
        {
            if (i->Attribute("value") == 0)
                return false;
        }
    return true;
}

bool xmlCheckRooms(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("room"); i != 0;
             i = i->NextSiblingElement("room"))
        {
            if (i->Attribute("id") == 0 ||
                i->Attribute("bg") == 0 ||
                !xmlCheckAreas(i->FirstChildElement("areas")))
                return false;
        }
    return true;
}

bool xmlCheckAreas(TiXmlElement *elem)
{
    int tmp;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("area"); i != 0;
             i = i->NextSiblingElement("area"))
        {
            if (i->Attribute("id") == 0 ||
                i->Attribute("enabled") == 0 ||
                i->QueryIntAttribute("x", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("y", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
                !xmlCheckDoEvents(i))
                return false;
        }
    return true;
}

bool xmlCheckItems(TiXmlElement *elem)
{
    int tmp;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("item"); i != 0;
             i = i->NextSiblingElement("item"))
        {
            if (i->Attribute("id") == 0 ||
                i->QueryIntAttribute("x", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("y", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
                i->Attribute("image") == 0 ||
                i->Attribute("room") == 0 ||
                !xmlCheckDoEvents(i))
                return false;
        }
    return true;
}

bool xmlCheckDoEvents(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("do_event"); i != 0;
             i = i->NextSiblingElement("do_event"))
        {
            if (i->Attribute("value") == 0)
                return false;
        }
    return true;
}

std::vector <TiXmlElement *> xmlGetAllChilds(TiXmlElement *elem, std::string id)
{
    std::vector <TiXmlElement *> childs;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement(id.c_str());
             i != 0;
             i = i->NextSiblingElement(id.c_str()))
        {
            childs.push_back(i);
        }

    return childs;
}
