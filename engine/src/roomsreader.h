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

#include "tinyxml.h"
#include "event.h"
#include "room.h"
#include "area.h"
#include "item.h"
#include "dialog.h"
#include "versioning.h"

#include <map> //std::map
#include <string> //std::string
#include <vector> //std::vector
#include <set> //std::set
#include <fstream> //std::ifstream
#include <sstream> //std::ostringstream

using std::string;

 /**
 *
 * \brief The RRNode class is used to navigate through xml tree.
 *
 * The class navigates through xml nodes and gets attributes from them.
 * Example:
 * \code
 * RRNode *node(validXmlElement);
 * node->gotoElement("my_element");
 * for (node->gotoChild("my_child"); !node->isNull(); node->gotoNext())
 *      //do something
 * \endcode
 */
class RRNode
{
    public:
        /**
         * \brief Creates a RRNode wrapping a TiXmlElement *.
         *
         * Methods attrStr and attrFloat work in the same way.
         * \param root  It will be the root element for this node.
         */
        RRNode(TiXmlElement *root);
        ~RRNode();
        /**
         * \brief Place RRNode at initial element.
         *
         * \return It returns the node itself, like gotoChild, gotoParent, gotoNext and gotoElement.
         */
        RRNode *gotoRoot();
        /**
         * \brief The class moves inside cursor to point the child with given name.
         *
         * \param name  Child name.
         * \return It returns the node itself.
         */
        RRNode *gotoChild(string name);
        /**
         * \brief The class moves inside cursor to point the parent.
         *
         * \return It returns the node itself.
         */
        RRNode *gotoParent();
        /**
         * \brief The class moves inside cursor to point next sibling with same name.
         *
         * \return It returns the node itself.
         */
        RRNode *gotoNext();
        /**
         * \brief The class searches in whole xml tree the element with given name.
         *
         * \return It returns the node itself.
         */
        RRNode *gotoElement(string name);
        /**
         * \brief A new element with given name is appended to the current node.
         *
         * A new element is appended and the cursor tracks it.
         *
         * \return It returns the node itself, updated with new element.
         */
        RRNode *appendElement(string name);
        /// Checks if node is a null node.
        bool isNull();
        /**
         * \brief Gets int data from an xml node attribute.
         *
         * Methods attrStr and attrFloat work in the same way.
         * \param name  Attribute name.
         * \return      Int value.
         */
        int attrInt(string name);
        /// Gets string data from an xml node attribute.
        string attrStr(string name);
        /// Gets float data from an xml node attribute.
        float attrFloat(string name);
        /// Puts a value in the given attribute.
        void setAttr(string name, string value);
        /**
         * \brief Uses current node to create an Event.
         *
         * This method creates and initializes an Event from node attributes information. Methods fetchRoom, fetchItem and fetchDialog work in the same way.
         * \return      An Event, fully initialized.
         */
        Event *fetchEvent();
        /// Uses current node to create a Room.
        Room *fetchRoom();
        /// Uses current node to create an Item.
        Item *fetchItem();
        /// Uses current node to create a Dialog.
        Dialog *fetchDialog();
    private:
        TiXmlElement *root;
        TiXmlElement *cursor;
        TiXmlElement *parent;
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
        /**
         * \brief Load world file from a valid path.
         *
         * \param filename  File path.
         * \return          True if file is correctly loaded and parsed.
         *                  False otherwise.
         */
        bool loadFromFile(string filename);
        /**
         * \brief Load world file from a valid string.
         *
         * \param content   String containing world data structure.
         * \return          True if file is correctly loaded and parsed.
         *                  False otherwise.
         */
        bool loadFromStr(string content);
        /// Parses the file and returns true if it's a correct world file.
        bool parse();
        /// Creates an empty document
        void loadEmptyDoc();
        /// Obtain crawler pointer, to navigate inside world file.
        RRNode *getCrawler();
        /// Saves current document to file
        void saveDoc(string filename);
    private:
        typedef bool (RoomsReader::*ParseMethod) (TiXmlElement *);

        std::map<string, ParseMethod> parse_map;
        TiXmlDocument *doc;
        RRNode *crawler;
        std::set<string> unique_ids_rooms;
        std::set<string> unique_ids_items;
        std::set<string> unique_ids_areas;
        std::set<string> unique_ids_events;
        std::set<string> unique_ids_vars;
        std::set<string> unique_ids_images;
        std::set<string> unique_ids_dialogs;
        int file_version; // initialized with parse(), modified in upgrade()
        string file_content; // string filled with file content
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

string floatToStr(float);

#endif // ROOMSREADER_H
