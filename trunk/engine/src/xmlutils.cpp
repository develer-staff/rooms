#include "xmlutils.h"

int xml::xmlReadInt(TiXmlElement *elem, std::string attribute)
{
    int tmp;
    elem->QueryIntAttribute(attribute.c_str(), &tmp);
    return tmp;
}

bool xml::xmlCheckDoc(TiXmlDocument *doc, const std::string &eng_ver)
{
    if (doc)
        return xml::xmlCheckRoot(doc->RootElement(), eng_ver) &&
               xml::xmlCheckImages(doc->RootElement()->FirstChildElement("images")) &&
               xml::xmlCheckVars(doc->RootElement()->FirstChildElement("vars")) &&
               xml::xmlCheckEvents(doc->RootElement()->FirstChildElement("events")) &&
               xml::xmlCheckRooms(doc->RootElement()->FirstChildElement("rooms")) &&
               xml::xmlCheckDialogs(doc->RootElement()->FirstChildElement("dialogs")) &&
               xml::xmlCheckItems(doc->RootElement()->FirstChildElement("items"));
    return false;
}

bool xml::xmlCheckRoot(TiXmlElement *elem, const std::string &eng_ver)
{
    int tmp;
    if (!elem)
        return false;
    std::string name = elem->Value();
    if (name != "world" ||
        elem->Attribute("name") == 0 ||
        elem->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
        elem->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
        std::string(elem->Attribute("version")) != eng_ver ||
        elem->Attribute("start") == 0)
        return false;
    return true;
}

bool xml::xmlCheckImages(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("img"); i != 0;
             i = i->NextSiblingElement("img"))
        {
            if (i->Attribute("file") == 0 ||
                ids.count(i->Attribute("file")) > 0)
                return false;
            else
                ids.insert(i->Attribute("file"));
        }
    return true;
}

bool xml::xmlCheckVars(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("var"); i != 0;
             i = i->NextSiblingElement("var"))
        {
            int tmp;
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->QueryIntAttribute("value", &tmp) != TIXML_SUCCESS)
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}


bool xml::xmlCheckEvents(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
    {
        for (TiXmlElement *i = elem->FirstChildElement("event"); i != 0;
             i = i->NextSiblingElement("event"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                !xmlCheckActions(i->FirstChildElement("actions_if")) ||
                !xmlCheckReqs(i->FirstChildElement("requirements")))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    }
    return true;
}

bool xml::xmlCheckActions(TiXmlElement *elem)
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

bool xml::xmlCheckParams(TiXmlElement *elem)
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

bool xml::xmlCheckDialogSteps(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("step"); i != 0;
             i = i->NextSiblingElement("step"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->Attribute("text") == 0 ||
                !xmlCheckReqs(i->FirstChildElement("requirements")) ||
                !xmlCheckActions(i->FirstChildElement("actions")))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}

bool xml::xmlCheckDialogs(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("dialog"); i != 0;
             i = i->NextSiblingElement("dialog"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->Attribute("start") == 0 ||
                !xmlCheckDialogSteps(i))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}

bool xml::xmlCheckReqs(TiXmlElement *elem)
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

bool xml::xmlCheckRooms(TiXmlElement *elem)
{
    std::set<std::string> ids;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("room"); i != 0;
             i = i->NextSiblingElement("room"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->Attribute("bg") == 0 ||
                !xmlCheckAreas(i->FirstChildElement("areas")))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}

bool xml::xmlCheckAreas(TiXmlElement *elem)
{
    std::set<std::string> ids;
    int tmp;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("area"); i != 0;
             i = i->NextSiblingElement("area"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->QueryIntAttribute("x", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("y", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
                !xmlCheckDoEvents(i))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}

bool xml::xmlCheckItems(TiXmlElement *elem)
{
    std::set<std::string> ids;
    int tmp;
    if (elem)
        for (TiXmlElement *i = elem->FirstChildElement("item"); i != 0;
             i = i->NextSiblingElement("item"))
        {
            if (i->Attribute("id") == 0 ||
                ids.count(i->Attribute("id")) > 0 ||
                i->QueryIntAttribute("x", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("y", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("width", &tmp) != TIXML_SUCCESS ||
                i->QueryIntAttribute("height", &tmp) != TIXML_SUCCESS ||
                i->Attribute("image") == 0 ||
                i->Attribute("room") == 0 ||
                !xmlCheckDoEvents(i))
                return false;
            else
                ids.insert(i->Attribute("id"));
        }
    return true;
}

bool xml::xmlCheckDoEvents(TiXmlElement *elem)
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

std::vector <TiXmlElement *> xml::xmlGetAllChilds(TiXmlElement *elem, std::string id)
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
