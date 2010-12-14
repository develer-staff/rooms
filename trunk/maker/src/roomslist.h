#ifndef ROOMSLIST_H
#define ROOMSLIST_H

#include <QListView>

class RoomsList : public QListView
{
    Q_OBJECT

public:
    explicit RoomsList(QWidget *parent = 0);

};

#endif // ROOMSLIST_H
