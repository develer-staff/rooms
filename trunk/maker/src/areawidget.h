#ifndef AREAWIDGET_H
#define AREAWIDGET_H

#include <QWidget>
#include "core/area.h"

class AreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AreaWidget(const Area *area, QWidget *parent = 0);

};

#endif // AREAWIDGET_H
