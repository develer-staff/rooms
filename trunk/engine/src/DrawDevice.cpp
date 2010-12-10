#include "DrawDevice.h"
#include "RoomsEngine.h"
#include "RoomsManager.h"

DrawDevice::DrawDevice(RoomsEngine *engine, QWidget *parent): QWidget(parent)
{
    //ctor
    _engine = engine;
    RoomsManager *man = _engine->getRoomsManager();
    parentWidget()->resize(man->width(), man->height());
    parentWidget()->setWindowTitle(man->name().c_str());
    //TODO: get from engine world size and world's name
}

DrawDevice::~DrawDevice()
{
    //dtor
    std::map<std::string, QImage *>::iterator i;
    for (i = _images.begin(); i != _images.end(); i++)
    {
        delete i->second;
    }
    _images.clear();
}

#include <iostream>

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

void DrawDevice::paintEvent(QPaintEvent *event)
{
    QPainter _painter(this);
    _painter.drawLine(0, 0, 800, 600);
    //TODO: get room attributes from engine and draw all
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    _engine->click(event->x(), event->y());
    //TODO: test if room is changed and draw it again
}

bool DrawDevice::fileExists(std::string filename)
{
    std::ifstream ifile(filename.c_str());
    return ifile;
}

