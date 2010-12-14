#include "drawdevice.h"
#include "engine.h"
#include "roomsmanager.h"
#include "room.h"
#include "item.h"

DrawDevice::DrawDevice(Engine *engine, QWidget *parent): QWidget(parent)
{
    _engine = engine;
}

DrawDevice::~DrawDevice()
{
    std::map<std::string, QImage *>::iterator i;
    for (i = _images.begin(); i != _images.end(); i++)
    {
        delete i->second;
    }
    _images.clear();
}

void DrawDevice::initialize()
{
    RoomsManager *man = _engine->getRoomsManager();
    parentWidget()->resize(man->width(), man->height());
    parentWidget()->setWindowTitle(man->name().c_str());
}

bool DrawDevice::loadImage(std::string id, std::string filename)
{
    if (fileExists(filename))
    {
        _images[id] = new QImage(filename.c_str());
        return true;
    } else {
        return false;
    }
}

bool DrawDevice::fileExists(std::string filename)
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
    QPainter _painter(this);
    switch (_engine->state())
    {
        case Engine::GAME:
        {
            //Draw room
            Room *room = _engine->getRoomsManager()->currentRoom();
            QImage *bg = _images[room->bg()];
            QRectF rect(0.0, 0.0, width(), height());
            std::vector <Item *> items = room->items();
            _painter.drawImage(rect, *bg);
            //Draw items
            for (std::vector<Item *>::iterator i = items.begin();
                 i != items.end(); i++)
            {
                QImage *img = _images[(*i)->image()];
                QRectF irect((*i)->x(), (*i)->y(), (*i)->w(), (*i)->h());
                _painter.drawImage(irect, *img);
            }
            break;
        }
    }
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    _engine->click(event->x(), event->y());
    repaint(QRect(0, 0, width(), height()));
}


