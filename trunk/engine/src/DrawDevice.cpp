#include "DrawDevice.h"
#include "DrawManager.h"

DrawDevice::DrawDevice(DrawManager *manager, QWidget *parent): QWidget(parent)
{
    //ctor
    _manager = manager;
    parentWidget()->resize(800, 600);
    parentWidget()->setWindowTitle("Rooms Engine");
}

void DrawDevice::paintEvent(QPaintEvent *event)
{
    QPainter _painter(this);
    _painter.drawLine(0, 0, 800, 600);
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    _manager->click(event->x(), event->y());
}
