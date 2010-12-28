#include "action.h"

Action::Action(ActionType type, QString room)
{
    _type = type;
    _room = room;
}

void Action::setType(const int type)
{
    _type = (ActionType)type;
}

Action::ActionType Action::type() const
{
    return _type;
}

void Action::setRoom(const QString &room)
{
    _room = room;
}

QString Action::room() const
{
    return _room;
}

QString Action::toHumanReadable() const
{
    return "Prova prova";
}
