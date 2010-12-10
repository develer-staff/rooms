#ifndef ROOM_H
#define ROOM_H

#include <QObject>

class Room : public QObject
{
    Q_OBJECT

public:
    Room(QString const& name, QObject *parent = 0);
    ~Room();

private:
    QString name;
};

#endif // ROOM_H
