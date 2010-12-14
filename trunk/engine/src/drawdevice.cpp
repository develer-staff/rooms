#include "drawdevice.h"
#include "engine.h"
#include "roomsmanager.h"
#include "room.h"
#include "item.h"

DrawDevice::DrawDevice(Engine *engine, QWidget *parent): QWidget(parent)
{
    _engine = engine;
    //TODO: get from engine world size and world's name
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
    //TODO: handle errors and unique name check
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
    //TODO: get room attributes from engine and draw all
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
    //TODO: test if room is changed and draw it again
    repaint(QRect(0, 0, width(), height()));
}


