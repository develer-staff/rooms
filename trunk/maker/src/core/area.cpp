#include "area.h"

Area::Area(const QString &name, const QPoint &pos, const QSize &size, QObject *parent) :
    QObject(parent)
{
    _name = name;
    _size = size;
    _pos = pos;
}

QRect Area::rect() const
{
    return QRect(QPoint(0, 0), _size);
}

QString Area::name() const
{
    return _name;
}

void Area::setPos(const QPoint &pos)
{
    _pos = pos;
}

QPoint Area::pos() const
{
    return _pos;
}

void Area::setName(const QString &name)
{
    _name = name;
}

Action *Area::addAction()
{
    Action *action = new Action;
    _actions.append(action);
    return action;
}

QList<Action *> Area::actions() const
{
    return _actions;
}

void Area::setActions(const QList<Action*> &actions)
{
    _actions = actions;
}
