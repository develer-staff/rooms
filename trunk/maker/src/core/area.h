#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QRect>

class Area : public QObject
{
    Q_OBJECT

public:
    Area(const QString &name, const QRect &rect, QObject *parent = 0);
    void setPos(const QPoint &point);

    QRect rect() const;
    QString name() const;

private:
    QString _name;
    QRect _rect;
};

#endif // AREA_H
