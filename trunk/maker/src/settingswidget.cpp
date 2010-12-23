#include "settingswidget.h"

SettingsWidget::SettingsWidget(World *world, QWidget *parent) :
    QWidget(parent)
{
    setWorld(world);
    setupUi();

    setFixedWidth(200);

    connect(room_name, SIGNAL(textEdited(QString)), this, SLOT(validateRoomName(QString)));
    connect(room_name, SIGNAL(editingFinished()), this, SLOT(setRoomName()));
    connect(area_name, SIGNAL(textEdited(QString)), this, SLOT(validateAreaName(QString)));
    connect(area_name, SIGNAL(editingFinished()), this, SLOT(setAreaName()));

    area_settings->hide();
}

void SettingsWidget::setWorld(World *world)
{
    _world = world;
}

void SettingsWidget::updateRoomSettings(Room *room)
{
    active_room = room;
    area_settings->hide();
    room_settings->show();
    room_name->setText(room->name());
}

void SettingsWidget::updateAreaSettings(Area *area)
{
    active_area = area;
    room_settings->hide();
    area_settings->show();
    area_name->setText(area->name());
}

void SettingsWidget::validateRoomName(const QString &text)
{
    if (_world->rooms()->roomExists(text))
    {
        QPalette palette = room_name->palette();
        palette.setColor(QPalette::Base, QColor(255, 0, 0));
        room_name->setPalette(palette);
    }
    else
        room_name->setPalette(QPalette(QPalette::Base, Qt::white));
}

void SettingsWidget::setRoomName()
{
    if (!_world->rooms()->roomExists(room_name->text()))
        active_room->setName(room_name->text());
    else
        room_name->setText(active_room->name());

    room_name->setPalette(QPalette(QPalette::Base, Qt::white));
}

void SettingsWidget::validateAreaName(const QString &text)
{
    if (active_room->areaExists(text))
    {
        QPalette palette = area_name->palette();
        palette.setColor(QPalette::Base, QColor(255, 0, 0));
        area_name->setPalette(palette);
    }
    else
        area_name->setPalette(QPalette(QPalette::Base, Qt::white));
}

void SettingsWidget::setAreaName()
{
    if (!active_room->areaExists(area_name->text()))
        active_area->setName(area_name->text());
    else
        area_name->setText(active_area->name());

    area_name->setPalette(QPalette(QPalette::Base, Qt::white));
}

void SettingsWidget::setupUi()
{
    //Room settings
    room_settings = new QGroupBox("Room settings", this);
    room_settings_layout = new QVBoxLayout(this);

    room_name_layout = new QHBoxLayout(this);
    room_name_label = new QLabel("Room name:", this);
    room_name = new QLineEdit(this);
    room_name_layout->addWidget(room_name_label);
    room_name_layout->addWidget(room_name);

    room_settings_layout->addLayout(room_name_layout);
    room_settings->setLayout(room_settings_layout);

    //Area settings
    area_settings = new QGroupBox("Area settings", this);
    area_settings_layout = new QVBoxLayout(this);

    area_name_layout = new QHBoxLayout(this);
    area_name_label = new QLabel("Area name:", this);
    area_name = new QLineEdit(this);
    area_name_layout->addWidget(area_name_label);
    area_name_layout->addWidget(area_name);

    area_settings_layout->addLayout(area_name_layout);
    area_settings->setLayout(area_settings_layout);

    //Settings
    settings_layout = new QVBoxLayout(this);
    settings_layout->addWidget(room_settings);
    settings_layout->addWidget(area_settings);
    spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    settings_layout->addSpacerItem(spacer);

    setLayout(settings_layout);
}
