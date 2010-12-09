#include "DrawDevice.h"

#include <iostream>

DrawDevice::DrawDevice(QWidget *parent): QWidget(parent)
{
    //ctor
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

}
