#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QRect>
#include "action.h"

class Area : public QObject
{
    Q_OBJECT

public:
    Area(const QString &name, const QRect &rect, QObject *parent = 0);
    void setPos(const QPoint &point);

    QRect rect() const;

    void setName(const QString &name);
    QString name() const;

    Action *addAction();
    QList<Action *> actions() const;

private:
    QList<Action *> _actions;
    QString _name;
    QRect _rect;
};

#endif // AREA_H
