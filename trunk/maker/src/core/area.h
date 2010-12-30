#ifndef AREA_H
#define AREA_H

#include <QRect>
#include "action.h"

class Area
{
public:
    Area(const QString &name, const QPoint &pos, const QSize &size);
    void setPos(const QPoint &pos);

    QRect rect() const;
    QPoint pos() const;

    void setName(const QString &name);
    QString name() const;

    Action *addAction();
    void setActions(const QList<Action*> &actions);
    QList<Action *> actions() const;

private:
    QList<Action *> _actions;
    QString _name;
    QSize _size;
    QPoint _pos;
};

#endif // AREA_H
