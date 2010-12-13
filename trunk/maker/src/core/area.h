#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QRect>

class Area : public QObject
{
    Q_OBJECT

public:
    Area(const QRect &rect, QObject *parent = 0);
};

#endif // AREA_H
