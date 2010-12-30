#ifndef ROOM_H
#define ROOM_H

#include <QPixmap>
#include "area.h"

class Room : public QObject
{
    Q_OBJECT

public:
    Room(const QString &name);

    Area *addArea(const QPoint &pos, const QSize &size);
    QList<Area*> areas() const;

    void setActiveArea(Area *area);
    Area *activeArea() const;

    void setBackground(const QPixmap &rect);
    QPixmap background() const;

    QPixmap icon() const;

    QString name() const;
    void setName(const QString &name);

    bool areaExists(const QString &name);

signals:
    void activeAreaChanged();
    void changed();

private:
    QList<Area*> _areas;
    QString _name;
    QPixmap _background;
    QPixmap _icon;
    int area_count;
    Area *active_area;
};

#endif // ROOM_H
