#include "xmlutils.h"

int std::xmlReadInt(TiXmlElement *elem, std::string attribute)
{
    int tmp;
    elem->QueryIntAttribute(attribute.c_str(), &tmp);
    return tmp;
}

bool std::xmlCheckDoc(TiXmlDocument *doc)
{
    if (doc)
        return doc->LoadFile() &&
               std::xmlCheckRoot(doc->RootElement()) &&
               std::xmlCheckImages(doc->RootElement()->FirstChildElement("images")) &&
               std::xmlCheckVars(doc->RootElement()->FirstChildElement("vars")) &&
               std::xmlCheckEvents(doc->RootElement()->FirstChildElement("events")) &&
               std::xmlCheckRooms(doc->RootElement()->FirstChildElement("rooms")) &&
               std::xmlCheckRooms(doc->RootElement()->FirstChildElement("items"));
    return false;
}

bool std::xmlCheckRoot(TiXmlElement *elem)
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

bool std::xmlCheckImages(TiXmlElement *elem)
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

bool std::xmlCheckVars(TiXmlElement *elem)
{
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("var"); i != 0;
             i = i->NextSiblingElement("var"))
        {
            int tmp;
            if (i->Attribute("id") == 0 ||
                i->QueryIntAttribute("value", &tmp) != TIXML_SUCCESS)
                return false;
        }
    return true;
}


bool std::xmlCheckEvents(TiXmlElement *elem)
{
    if (elem)
    {
        for (TiXmlElement *i = elem->FirstChildElement("event"); i != 0;
             i = i->NextSiblingElement("event"))
        {
            if (i->Attribute("id") == 0 ||
                !xmlCheckActions(i->FirstChildElement("actions_if")) ||
                !xmlCheckReqs(i->FirstChildElement("requirements")))
                return false;
        }
    }
    return true;
}

bool std::xmlCheckActions(TiXmlElement *elem)
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

bool std::xmlCheckParams(TiXmlElement *elem)
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

bool std::xmlCheckReqs(TiXmlElement *elem)
{
    if (elem)
    {
        for (TiXmlElement *i = elem->FirstChildElement("item_req"); i != 0;
             i = i->NextSiblingElement("item_req"))
        {
            if (i->Attribute("id") == 0 ||
                i->Attribute("value") == 0)
                return false;
        }
        int tmp;
        for (TiXmlElement *i = elem->FirstChildElement("var_req"); i != 0;
             i = i->NextSiblingElement("var_req"))
        {
            if (i->Attribute("id") == 0 ||
                i->QueryIntAttribute("value", &tmp) != TIXML_SUCCESS)
                return false;
        }
    }
    return true;
}

bool std::xmlCheckRooms(TiXmlElement *elem)
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

bool std::xmlCheckAreas(TiXmlElement *elem)
{
    int tmp;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("area"); i != 0;
             i = i->NextSiblingElement("area"))
        {
            if (i->Attribute("id") == 0 ||
                i->QueryIntAttribute("enabled", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("x", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("y", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
                !xmlCheckDoEvents(i))
                return false;
        }
    return true;
}

bool std::xmlCheckItems(TiXmlElement *elem)
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

bool std::xmlCheckDoEvents(TiXmlElement *elem)
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

std::vector <TiXmlElement *> std::xmlGetAllChilds(TiXmlElement *elem, std::string id)
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
