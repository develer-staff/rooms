/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: gui.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */

#ifndef GUI_H
#define GUI_H

#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map

using std::string;

/** \brief Simple rectangle class.
 *
 */
struct GuiRect
{
    /// Size and coordinates
    float x, y, w, h;
    GuiRect(){}
    GuiRect(float x_, float y_, float w_, float h_): x(x_), y(y_), w(w_), h(h_) {}
};

/** \brief This class contains drawable information.
 *
 * It's used by engine to represent what must be drawn and where.
 */
struct GuiData
{
    string text;
    GuiRect rect;
    string image;
};

/// A vector of GuiData structs.
typedef std::vector<GuiData> GuiDataVect;

/** \brief Base gui class. It can be clicked, it has a text and an image.
 *
 */
class GuiButton
{
    public:
        /** \brief Class creator.
         *
         * \param name      It's the id.
         * \param rect_     It's the shape.
         * \param text_     It's the caption.
         * \param image_    It's the image id.
         */
        GuiButton(string name, GuiRect rect_, string text_, string image_);
        /// Unique name.
        const string id;
        /// Checks if point is inside the button.
        virtual bool isInside(float x, float y);
        /// Sets button rectangle.
        void setRect(GuiRect rect_);
        /// Retuns button rectangle.
        GuiRect getRect();
        /// Sets caption text.
        virtual void setCaption(string text_);
        /// Activates button: it's virtual in order to specialize behavior in derived classes.
        virtual string activate(float x = 0, float y = 0);
        /// Returns the drawable representation of the object.
        virtual GuiDataVect getVisibleData();
        /// Sets visibility.
        bool visible;
    protected:
        GuiRect rect;
        string text;
        string image;
    private:
        // non-copiable
        GuiButton(const GuiButton &);
        void operator=(const GuiButton &);
};

/** \brief This class handles a GuiButton horizontal and vertical list.
 *
 * It supports horizontal and vertical scroll, and addiction and button removal.
 */
class GuiList: public GuiButton
{
    public:
        enum GuiListType
        {
            H_GUILIST,
            V_GUILIST
        };
        /** \brief Class creator.
         *
         * \param name      It's the id.
         * \param text_     It's the caption.
         * \param image_    It's the image id.
         * \param rect_     It's the shape.
         * \param item_rect_     It's the shape of each iteam inside the control.
         */
        GuiList(string name, string text_, string image_,  GuiRect rect_, GuiRect item_rect_, GuiListType type);
        ~GuiList();
        /// Scrolls items in a direction +1 (right/down) or -1 (left/up).
        void scroll(int direction);
        /// Creates a button, inserts it in the list and adjusts its shape.
        void addButton(string name, string text_, string image_);
        /// Removes a button from its id.
        void remButton(string name);
        /// Deletes all buttons and clears the list.
        void clear();
        /// Returns list's size.
        int size();
        /// Returns the drawable representation of the object.
        GuiDataVect getVisibleData();
        /// Activates the object in the list that is under the click.
        string activate(float x, float y);
    protected:
        std::vector<GuiButton *> items;
        GuiRect item_rect;
        void updateItemsRect();
        int begin, end;
        int cols, count;
        GuiListType type;
};

/** \brief This class handles a GuiButton that scrolls an horizontal list.
 *
 */
class GuiScrollButton: public GuiButton
{
    public:
        /** \brief Class creator.
         *
         * \param name      It's the id.
         * \param rect_     It's the shape.
         * \param text_     It's the caption.
         * \param image_    It's the image id.
         * \param list_     It's the list linked to this button.
         * \param direction_     It's the scroll direction (+1 or -1).
         */
        GuiScrollButton(string name, GuiRect rect_, string text_, string image_, GuiList *list_, int direction_);
        /// Activates the buttom performing the scroll.
        string activate(float x, float y);
    protected:
        GuiList *list;
        int direction;
};

/** \brief This class combines a GuiHList and its two scroll buttons.
 *
 * Near the GuiHList are placed two scroll buttons, handled as a single component.
 */
class GuiScrolledBar: public GuiList
{
    public:
        /** \brief Class creator.
         *
         * \param name      It's the id.
         * \param text_     It's the label caption. It's drawn upon the list.
         * \param image_    It's the image id.
         * \param rect_     It's the shape.
         * \param item_rect_     It's the shape of each iteam inside the control.
         * \param button_size     It's the shape of scroll buttons.
         * \param img_right     Right button's image.
         * \param img_left     Left button's image.
         */
        GuiScrolledBar(string name, string text_, string image_, GuiRect rect_,
                        GuiRect item_rect_, GuiRect button_size, string img_right,
                        string img_left, GuiList::GuiListType type);
        ~GuiScrolledBar();
        /// Returns the drawable representation of the object.
        GuiDataVect getVisibleData();
        /// Activates a scroll button or an item.
        string activate(float x, float y);
        /// Checks if point is inside the object's area.
        bool isInside(float x, float y);
        /// Sets the label upon the list.
        void setCaption(string text_);
    protected:
        GuiScrollButton *forward;
        GuiScrollButton *backward;
        GuiButton *label;
        GuiRect global_rect;
};

/** \brief This class handles all gui components and gets user input.
 *
 */
class GuiManager
{
    public:
        GuiManager();
        ~GuiManager();
        /// Returns the drawable representation of whole gui objects.
        GuiDataVect getVisibleData();
        /// Picks up a gui object by its name.
        GuiButton *getGuiObjByName(string name);
        /// Includes a GuiButton in the gui. GuiManager will handle its destruction.
        void addGuiObj(GuiButton *obj);
        /// Throwns user click and returns the id of activated item ("" otherwise).
        string click(float x, float y);
    private:
        std::map<string, GuiButton *> gui;
        // non-copiable
        GuiManager(const GuiManager &);
        void operator=(const GuiManager &);
};

#endif // GUI_H
