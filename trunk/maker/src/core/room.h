#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "area.h"

class Room : public QObject
{
    Q_OBJECT

public:
    Room(const QString &name, QObject *parent = 0);

    Area *addArea(const QRect &rect);

    void setBackground(const QPixmap &rect);
    QPixmap background() const;

    QPixmap icon() const;

    QString name() const;
    void setName(const QString &name);

    QList<Area*> areas() const;

    bool areaExists(const QString &name);

signals:
    void changed();

private:
    QList<Area*> _areas;
    QString _name;
    QPixmap _background;
    QPixmap _icon;
    int area_count;
};

#endif // ROOM_H
