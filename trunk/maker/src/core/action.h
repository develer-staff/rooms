#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QHash>

class Action
{

public:
    enum ActionType {
        ChangeRoom
    };
    Action(ActionType type = ChangeRoom, QString room = "");

    ActionType type() const;
    QString typeToString() const;

    QString room() const;

    QString toHumanReadable() const;

    void setType(const int type);
    void setRoom(const QString &room);

private:
    ActionType _type;
    QString _room;
    QHash<ActionType, QString> actions_hr;
    QHash<ActionType, QString> actions_str;
};

#endif // ACTION_H
