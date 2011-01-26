#include "gui.h"
#include "log.h"

extern Log logger;

GuiButton::GuiButton(string name, GuiRect rect_, string text_, string image_):
    id(name), visible(true), rect(rect_), text(text_), image(image_)
{
}

bool GuiButton::isInside(float x, float y)
{
    if (!visible)
        return false;
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
        return true;
    else
        return false;
}

void GuiButton::setRect(GuiRect rect_)
{
    rect = rect_;
}

void GuiButton::setCaption(string text_)
{
    text = text_;
}

GuiRect GuiButton::getRect()
{
    return rect;
}

string GuiButton::activate(float, float)
{
    return id;
}

GuiDataVect GuiButton::getVisibleData()
{
    GuiData data;
    GuiDataVect vect;
    data.text = text;
    data.image = image;
    data.rect = rect;
    vect.push_back(data);
    return vect;
}

GuiList::GuiList(string name, string text_, string image_, GuiRect rect_, GuiRect item_rect_, GuiListType type):
    GuiButton(name, rect_, text_, image_), item_rect(item_rect_), type(type)
{
    if (type == H_GUILIST)
        cols = rect.w / item_rect.w;
    else
        cols = rect.h / item_rect.h;
    count = 0;
    begin = 0;
    end = cols;
    updateItemsRect();
}

GuiList::~GuiList()
{
    clear();
}

int GuiList::size()
{
    return count;
}

void GuiList::addButton(string name, string text_, string image_)
{
    items.push_back(new GuiButton(name, item_rect, text_, image_));
    ++count;
    updateItemsRect();
}

void GuiList::remButton(string name)
{
    for (std::vector<GuiButton *>::iterator i = items.begin();
        i != items.end(); ++i)
    {
        if ((*i)->id == name)
        {
            delete (*i);
            items.erase(i);
            --count;
            updateItemsRect();
            return;
        }
    }
}

void GuiList::clear()
{
    for (std::vector<GuiButton *>::iterator i = items.begin();
        i != items.end(); ++i)
        delete (*i);
    begin = 0;
    end = cols;
    count = 0;
    items.clear();
}

void GuiList::scroll(int direction)
{
    begin += direction;
    end += direction;
    int size = items.size();
    if (end >= size)
    {
        end = size;
        begin = end - cols;
    }
    if (begin < 0)
    {
        begin = 0;
        end = begin + cols;
    }
    updateItemsRect();
}

void GuiList::updateItemsRect()
{
    for (int i = begin; i < end && i < items.size(); ++i)
    {
        GuiButton *item = items.at(i);
        GuiRect r = item->getRect();
        if (type == H_GUILIST)
        {
            r.x = rect.x + r.w * (i - begin);
            r.y = rect.y;
        }
        else
        {
            r.x = rect.x;
            r.y = rect.y + r.h * (i - begin);
        }
        item->setRect(r);
    }

}

GuiDataVect GuiList::getVisibleData()
{
    GuiDataVect vect;
    if (size() == 0)
        return vect;
    for (int i = begin; i < end && i < items.size(); ++i)
    {
        vect.push_back(items.at(i)->getVisibleData().front());
    }
    return vect;
}

string GuiList::activate(float x, float y)
{
    for (int i = begin; i < end && i < items.size(); ++i)
    {
        if (items.at(i)->isInside(x, y))
            return items.at(i)->activate(x, y);
    }
    return "";
}

GuiScrollButton::GuiScrollButton(string name, GuiRect rect_, string text_, string image_, GuiList *list_, int direction_):
    GuiButton(name, rect_, text_, image_), list(list_), direction(direction_)
{
}

string GuiScrollButton::activate(float, float)
{
    list->scroll(direction);
    return ""; // GuiScrollButton event are all inside GuiManager, and they're invisible outside
}

GuiScrolledHBar::GuiScrolledHBar(string name, string text_, string image_, GuiRect rect_, GuiRect item_rect_, GuiRect button_size, string img_right, string img_left):
    GuiList(name, text_, image_, GuiRect(rect_.x + button_size.w, rect_.y, rect_.w - 2 * button_size.w, rect_.h), item_rect_, GuiList::H_GUILIST)
{
    GuiRect r = button_size;
    r.x = rect.x + rect.w;
    r.y = rect.y;
    forward = new GuiScrollButton("", r, "", img_right, this, +1);
    r.x = rect.x - r.w;
    backward = new GuiScrollButton("", r, "", img_left, this, -1);
    label = new GuiButton("", GuiRect(rect.x, rect.y - 0.01, rect.w, 0.01), "", "");
}

GuiScrolledHBar::~GuiScrolledHBar()
{
    delete forward;
    delete backward;
    delete label;
}

void GuiScrolledHBar::setCaption(string text_)
{
    label->setCaption(text_);
}

GuiDataVect GuiScrolledHBar::getVisibleData()
{
    GuiDataVect vect;
    GuiDataVect list_data = GuiList::getVisibleData();
    vect.insert(vect.end(), list_data.begin(), list_data.end());
    vect.push_back(forward->getVisibleData().front());
    vect.push_back(backward->getVisibleData().front());
    vect.push_back(label->getVisibleData().front());
    return vect;
}

string GuiScrolledHBar::activate(float x, float y)
{
    if (forward->isInside(x, y))
        return forward->activate(x, y);
    if (backward->isInside(x, y))
        return backward->activate(x, y);
    return GuiList::activate(x, y);
}

bool GuiScrolledHBar::isInside(float x, float y)
{
    return (GuiList::isInside(x, y) || forward->isInside(x, y) || backward->isInside(x, y));
}

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{
    for (std::map<string, GuiButton *>::iterator i = gui.begin();
        i != gui.end(); ++i)
        delete i->second;
    gui.clear();
}

GuiButton *GuiManager::getGuiObjByName(string name)
{
    return gui.find(name)->second;
}

void GuiManager::addGuiObj(GuiButton *obj)
{
    gui[obj->id] = obj;
}

string GuiManager::click(float x, float y)
{
    for (std::map<string, GuiButton *>::iterator i = gui.begin();
        i != gui.end(); ++i)
    {
        if (i->second->isInside(x, y))
        {
            return i->second->activate(x, y);
        }
    }
    return "";
}

GuiDataVect GuiManager::getVisibleData()
{
    GuiDataVect vect;
    for (std::map<string, GuiButton *>::iterator i = gui.begin();
        i != gui.end(); ++i)
    {
        GuiButton *gui_obj = i->second;
        if (gui_obj->visible)
        {
            GuiDataVect dv = gui_obj->getVisibleData();
            vect.insert(vect.end(), dv.begin(), dv.end());
        }
    }
    return vect;
}
