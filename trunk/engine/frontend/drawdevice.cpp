#include "drawdevice.h"


DrawDevice::DrawDevice(Engine *eng, QWidget *parent): QWidget(parent)
{
    engine = eng;
}

DrawDevice::~DrawDevice()
{
    for (std::map<string, QPixmap *>::iterator i = images.begin();
         i != images.end(); ++i)
    {
        delete i->second;
    }
    images.clear();
}

void DrawDevice::initialize()
{
    setMouseTracking(true);
    std::vector<string> images = engine->getImgNames();
    for (std::vector<string>::iterator i = images.begin();
         i != images.end(); ++i)
         loadImage(*i);
}

bool DrawDevice::loadImage(string filename)
{
    if (fileExists(filename))
    {
        images[filename] = new QPixmap(filename.c_str());
        return true;
    }
    else
    {
        return false;
    }
}

void DrawDevice::quit(int status)
{
    qApp->exit(status);
}

void DrawDevice::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    switch (engine->state())
    {
        case Engine::GAME:
        {
            //Draw room
            Room *room = engine->getRoomsManager()->currentRoom();
            QPixmap *bg = images[room->bg()];
            QRect rect(0, 0, width(), height());
            std::vector <Item *> items = room->items();
            painter.drawPixmap(rect, *bg);
            //Draw items
            for (std::vector<Item *>::iterator i = items.begin();
                 i != items.end(); ++i)
            {
                QPixmap *img = images[(*i)->image()];
                QRect irect((*i)->x(), (*i)->y(), (*i)->w(), (*i)->h());
                painter.drawPixmap(irect, *img);
            }
            painter.drawText(20, height() - 20, item_text.c_str());
            break;
        }
    }
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    engine->click(event->x(), event->y());
    update();
}
void DrawDevice::mouseMoveEvent(QMouseEvent *event)
{
    Item *item = engine->getRoomsManager()->currentRoom()->itemAt(event->x(),
                                                                  event->y());
    Area *area = engine->getRoomsManager()->currentRoom()->areaAt(event->x(),
                                                                  event->y());
    if (item != 0)
        item_text = item->id;
    else
        item_text = "";

    if (item != 0)
        setCursor(Qt::OpenHandCursor);
    else if (area != 0)
        setCursor(Qt::PointingHandCursor);
    else
        setCursor(Qt::ArrowCursor);

    update();
}


