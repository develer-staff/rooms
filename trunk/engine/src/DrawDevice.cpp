#include "DrawDevice.h"

DrawDevice::DrawDevice(QWidget *parent) : QWidget(parent)
{
    //ctor
}

/*DrawDevice::~DrawDevice()
*{
*
*}
*/
void DrawDevice::paintEvent(QPaintEvent *event)
{
    QPainter _painter(this);
    _painter.drawLine(0, 0, 800, 600);
}
