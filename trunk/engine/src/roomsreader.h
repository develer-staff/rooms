/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: roomsreader.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */

#ifndef ROOMSREADER_H
#define ROOMSREADER_H

#include "../lib/tinyxml/tinyxml.h"
#include "event.h"
#include "room.h"
#include "area.h"
#include "item.h"
#include "dialog.h"

#include <map> //std::map
#include <string> //std::string
#include <vector> //std::vector
#include <set> //std::set
#include <fstream> //std::ifstream

using std::string;

 /**
 *
 * \brief The RRNode class is used to navigate through xml tree.
 *
 * The class navigates through xml nodes and gets attributes from them.
 */
class RRNode
{
    public:
        RRNode(TiXmlElement *root);
        ~RRNode();
        RRNode *gotoRoot();
        RRNode *gotoChild(string name);
        RRNode *gotoParent();
        RRNode *gotoNext();
        RRNode *gotoElement(string name);
        bool isNull();
        int attrInt(string name);
        string attrStr(string name);
        float attrFloat(string name);
        Event *fetchEvent();
        Room *fetchRoom();
        Item *fetchItem();
        Dialog *fetchDialog();
    private:
        TiXmlElement *root;
        TiXmlElement *cursor;
        TiXmlElement *findElement(TiXmlElement *elem, string name);
};


 /**
 *
 * \brief The RoomsReader class takes care of world file.
 *
 * The class loads xml world file, parses it and permits navigation through
 * xml nodes.
 */
class RoomsReader
{
    public:
        enum AttributeType
        {
            ATTR_INT,
            ATTR_STR,
            ATTR_FLOAT
        };
        RoomsReader();
        ~RoomsReader();
        bool loadFromFile(string filename);
        bool loadFromStr(string content);
        RRNode *getCrawler();
    private:
        typedef bool (RoomsReader::*ParseMethod) (TiXmlElement *);
        std::map<string, ParseMethod> parse_map;
        TiXmlDocument doc;
        RRNode *crawler;
        std::set<string> unique_ids_rooms;
        std::set<string> unique_ids_items;
        std::set<string> unique_ids_areas;
        std::set<string> unique_ids_events;
        std::set<string> unique_ids_vars;
        std::set<string> unique_ids_images;
        std::set<string> unique_ids_dialogs;
        bool parse();
        bool parseElement(TiXmlElement *elem);
        bool parseWorld(TiXmlElement *elem);
        bool parseRoom(TiXmlElement *elem);
        bool parseAction(TiXmlElement *elem);
        bool parseEvent(TiXmlElement *elem);
        bool parseDialog(TiXmlElement *elem);
        bool parseDialogStep(TiXmlElement *elem);
        bool parseVar(TiXmlElement *elem);
        bool parseArea(TiXmlElement *elem);
        bool parseItem(TiXmlElement *elem);
        bool parseParam(TiXmlElement *elem);
        bool parseItemReq(TiXmlElement *elem);
        bool parseVarReq(TiXmlElement *elem);
        bool parseImages(TiXmlElement *elem);
        bool parseAttr(TiXmlElement *elem, string name, AttributeType type);
        bool checkUniqueId(std::set<string> &ids, const string id);
        bool checkParent(TiXmlElement *elem, string parent_name);
};

#endif // ROOMSREADER_H
