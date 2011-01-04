#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include "wizard.h"
#include "core/world.h"
#include "roomslist.h"
#include "roomview.h"
#include "settingswidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void saveAsProject();

private:
    void setupUi();
    QString current_project;
    QString createXml() const;
    World *createWorld(const QDomDocument &doc);
    QWidget *widget;
    QGridLayout *layout;
    QSpacerItem *vspacer;
    QSpacerItem *hspacer;
    RoomsList *rooms_list;
    RoomView *room_view;
    SettingsWidget *settings;
    Ui::MainWindow *ui;
    Wizard *wizard;
    World *world;
    RoomsModel *rooms;
};

#endif // MAINWINDOW_H
