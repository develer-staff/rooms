#include "DrawDevice.h"
#include "RoomsEngine.h"

DrawDevice::DrawDevice(RoomsEngine *engine, QWidget *parent): QWidget(parent)
{
    //ctor
    _engine = engine;
    parentWidget()->resize(800, 600);
    parentWidget()->setWindowTitle("Rooms Engine");
    //TODO: get from engine world size and world's name
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
