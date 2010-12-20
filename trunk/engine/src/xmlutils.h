#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include "../lib/tinyxml/tinyxml.h"

#include <string> //std::string
#include <vector> //std::vector

namespace std
{
    std::vector <TiXmlElement *> xmlGetAllChilds(TiXmlElement *elem, std::string id);
    bool xmlCheckDoc(TiXmlDocument *doc);
    bool xmlCheckRoot(TiXmlElement *elem);
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
}

#endif // XMLMANAGER_H
