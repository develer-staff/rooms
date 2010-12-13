#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include "area.h"

class Room : public QObject
{
    Q_OBJECT

public:
    Room(const QString &name, QObject *parent = 0);
    ~Room();
    bool addArea(const QPoint &p1, const QPoint &p2);
    void setBackgroundFile(const QString &backgroundFile);

private:
    QVector<Area*> *areas;
    QString name;
    QString backgroundFile;
};

#endif // ROOM_H
