#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include "core/world.h"

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(World *world, QWidget *parent = 0);
    void setWorld(World *world);

public slots:
    void updateRoomSettings(Room *room);
    void updateAreaSettings(Area *area);
    void validateRoomName(const QString &text);
    void validateAreaName(const QString &text);
    void setRoomName();
    void setAreaName();
    void newAction();

private:
    void setupUi();

    QVBoxLayout *settings_layout;

    QGroupBox *room_settings;
    QVBoxLayout *room_settings_layout;
    QHBoxLayout *room_name_layout;
    QLabel *room_name_label;
    QLineEdit *room_name;

    QLabel *actions_label;

    QHBoxLayout *action_comboboxes_layout;
    QComboBox *action_combobox;
    QComboBox *room_combobox;

    QHBoxLayout *new_action_layout;
    QPushButton *new_action_button;

    QGroupBox *area_settings;
    QVBoxLayout *area_settings_layout;
    QHBoxLayout *area_name_layout;
    QLabel *area_name_label;
    QLineEdit *area_name;

    QListWidget *actions_list;

    QSpacerItem *vspacer;
    QSpacerItem *hspacer;

    Area *active_area;
    Room *active_room;
    World *_world;
};

#endif // SETTINGSWIDGET_H
