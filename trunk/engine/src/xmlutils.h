#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include "../lib/tinyxml/tinyxml.h"

#include <string> //std::string
#include <vector> //std::vector
#include <set> //std::set

namespace xml
{
    std::vector <TiXmlElement *> xmlGetAllChilds(TiXmlElement *elem, std::string id);
    bool xmlCheckDoc(TiXmlDocument *doc, const std::string &eng_ver);
    bool xmlCheckRoot(TiXmlElement *elem, const std::string &eng_ver);
    bool xmlCheckRooms(TiXmlElement *elem);
    bool xmlCheckImages(TiXmlElement *elem);
    bool xmlCheckVars(TiXmlElement *elem);
    bool xmlCheckEvents(TiXmlElement *elem);
    bool xmlCheckActions(TiXmlElement *elem);
    bool xmlCheckParams(TiXmlElement *elem);
    bool xmlCheckReqs(TiXmlElement *elem);
    bool xmlCheckAreas(TiXmlElement *elem);
    bool xmlCheckItems(TiXmlElement *elem);
    bool xmlCheckDoEvents(TiXmlElement *elem);
    bool xmlCheckDialogs(TiXmlElement *elem);
    bool xmlCheckDialogSteps(TiXmlElement *elem);
    int xmlReadInt(TiXmlElement *elem, std::string attribute);
}

#endif // XMLMANAGER_H
