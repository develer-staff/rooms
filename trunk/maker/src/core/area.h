#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QRect>
#include "action.h"

class Area : public QObject
{
    Q_OBJECT

public:
    Area(const QString &name, const QPoint &pos, const QSize &size, QObject *parent = 0);
    void setPos(const QPoint &pos);

    QRect rect() const;
    QPoint pos() const;

    void setName(const QString &name);
    QString name() const;

    Action *addAction();
    QList<Action *> actions() const;
    void setActions(const QList<Action*> &actions);

private:
    QList<Action *> _actions;
    QString _name;
    QSize _size;
    QPoint _pos;
};

#endif // AREA_H
