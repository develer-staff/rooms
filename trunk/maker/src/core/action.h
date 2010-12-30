#ifndef ACTION_H
#define ACTION_H

#include <QHash>

class Action
{

public:
    enum ActionType {
        ChangeRoom
    };
    Action(ActionType type = ChangeRoom, QString room = "");

    void setType(const int type);
    ActionType type() const;

    void setType(const QString &type);
    QString typeToString() const;

    void setRoom(const QString &room);
    QString room() const;

    QString toHumanReadable() const;

private:
    ActionType _type;
    QString _room;
    QHash<ActionType, QString> actions_hr;
    QHash<ActionType, QString> actions_str;
};

#endif // ACTION_H
