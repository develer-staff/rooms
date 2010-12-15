#include "drawdevice.h"

DrawDevice::DrawDevice(Engine *eng, QWidget *parent): QWidget(parent)
{
    engine = eng;
}

DrawDevice::~DrawDevice()
{
    for (std::map<string, QImage *>::iterator i = images.begin();
         i != images.end(); ++i)
    {
        delete i->second;
    }
    images.clear();
}

void DrawDevice::initialize()
{
    setMouseTracking(true);
    RoomsManager *man = engine->getRoomsManager();
    parentWidget()->resize(man->width(), man->height());
    parentWidget()->setWindowTitle(man->name().c_str());
    std::vector<std::pair<string, string> > images = engine->getImgNames();
    for (std::vector<std::pair<string, string> >::iterator i = images.begin();
         i != images.end(); ++i)
         loadImage((*i).first, (*i).second);
}

bool DrawDevice::loadImage(string id, string filename)
{
    if (fileExists(filename))
    {
        images[id] = new QImage(filename.c_str());
        return true;
    }
    else
    {
        return false;
    }
}

bool DrawDevice::fileExists(string filename)
{
    std::ifstream ifile(filename.c_str());
    return ifile;
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
            QImage *bg = images[room->bg()];
            QRectF rect(0.0, 0.0, width(), height());
            std::vector <Item *> items = room->items();
            painter.drawImage(rect, *bg);
            //Draw items
            for (std::vector<Item *>::iterator i = items.begin();
                 i != items.end(); ++i)
            {
                QImage *img = images[(*i)->image()];
                QRectF irect((*i)->x(), (*i)->y(), (*i)->w(), (*i)->h());
                painter.drawImage(irect, *img);
            }
            painter.drawText(20, height() - 20, item_text.c_str());
            break;
        }
    }
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    engine->click(event->x(), event->y());
    repaint(QRect(0, 0, width(), height()));
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

    repaint(QRect(0, 0, width(), height()));
}


