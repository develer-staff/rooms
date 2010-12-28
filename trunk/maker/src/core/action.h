#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT

public:
    enum ActionType {
        ChangeRoom
    };
    Action(ActionType type = ChangeRoom, QString room = "", QObject *parent = 0);

    ActionType type() const;

    QString room() const;

    QString toHumanReadable() const;

public slots:
    void setType(const int type);
    void setRoom(const QString &room);

private:
    ActionType _type;
    QString _room;
};

#endif // ACTION_H
