#include "area.h"

Area::Area(const QString &name, const QRect &rect, QObject *parent) :
    QObject(parent)
{
    _name = name;
    _rect = rect;
}

QRect Area::rect() const
{
    return _rect;
}

QString Area::name() const
{
    return _name;
}

void Area::setPos(const QPoint &point)
{
    _rect.moveTo(point);
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
