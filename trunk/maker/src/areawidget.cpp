#include "areawidget.h"

AreaWidget::AreaWidget(const Area *area, QWidget *parent) :
    QWidget(parent)
{
    setPalette(QPalette(Qt::red));
    setWindowOpacity(0.5);
    setGeometry(area->rect());
}
