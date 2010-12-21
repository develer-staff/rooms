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
    void addArea(const QString &name, const QRect &rect);

    void setBackground(const QPixmap &rect);
    QPixmap background() const;

    QPixmap icon() const;

    QString name() const;

    QList<Area*> areas() const;

private:
    QList<Area*> _areas;
    QString _name;
    QPixmap _background;
    QPixmap _icon;
};

#endif // ROOM_H
