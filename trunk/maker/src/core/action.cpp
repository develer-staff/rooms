#include "action.h"

Action::Action(ActionType type, QString room)
{
    _type = type;
    _room = room;
    actions_str.insert(ChangeRoom, "ROOM_GOTO");
    actions_hr.insert(ChangeRoom, "Go to room");
}

void Action::setType(const int type)
{
    _type = (ActionType)type;
}

void Action::setType(const QString &type)
{
    _type = actions_str.key(type);
}

Action::ActionType Action::type() const
{
    return _type;
}

QString Action::typeToString() const
{
    return actions_str[_type];
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
    return actions_hr[_type] + " " + _room;
}
