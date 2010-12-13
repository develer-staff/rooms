#ifndef ROOM_H
#define ROOM_H

#include <QObject>

class Room : public QObject
{
    Q_OBJECT

public:
    Room(const QString &name, QObject *parent = 0);
    ~Room();
    void setBackgroundFile(const QString &backgroundFile);

private:
    QString name;
    QString backgroundFile;
};

#endif // ROOM_H
