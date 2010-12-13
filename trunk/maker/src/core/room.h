#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>
#include <QRect>
#include <QPixmap>
#include "area.h"

class Room : public QObject
{
    Q_OBJECT

public:
    Room(const QString &name, QObject *parent = 0);
    ~Room();
    bool addArea(const QRect &rect);
    void setBackground(const QPixmap &rect);

private:
    QVector<Area*> *areas;
    QString name;
    QPixmap background;
};

#endif // ROOM_H
