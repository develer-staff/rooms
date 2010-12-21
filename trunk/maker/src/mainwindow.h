#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wizard.h"
#include "core/world.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void resizeRoomView();
    void updateRoomSettings(Room *room);
    void updateAreaSettings(Area *area);

private:
    Ui::MainWindow *ui;
    Wizard *wizard;
    World *world;
};

#endif // MAINWINDOW_H
