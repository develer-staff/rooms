#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QRect>

class Area : public QObject
{
    Q_OBJECT

public:
    Area(const QRect &rect, QObject *parent = 0);

    QRect rect() const;

private:
    QRect _rect;
};

#endif // AREA_H
