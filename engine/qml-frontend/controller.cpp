#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) :
    QObject(parent),
    _t(0),
    current_room("")
{
    engine = new Engine();
    if (!engine->loadWorldFromFile("world.rooms")) {
        engine->getRoomsManager()->setRoomSize(0,0);
    }
    current_state = Controller::State(engine->state());
    connect(this, SIGNAL(tChanged()), this, SLOT(update()));
}

Controller::~Controller()
{
    delete engine;
}

int Controller::windowWidth() const
{
    return engine->getRoomsManager()->width();
}

void Controller::setWindowWidth(int width)
{
    engine->getRoomsManager()->setRoomSize(width, windowHeight());
    emit windowWidthChanged();
}

int Controller::windowHeight() const
{
    return engine->getRoomsManager()->height();
}

void Controller::setWindowHeight(int height)
{
    engine->getRoomsManager()->setRoomSize(windowWidth(), height);
    emit windowHeightChanged();
}

void Controller::setT(int t)
{
    if (t == _t)
        return;
    _t = t;
    emit tChanged();
}

QString Controller::room() const
{
    return current_room;
}

Controller::State Controller::state() const
{
    return Controller::State(engine->state());
}

void Controller::update()
{
    GuiDataVect data = engine->getVisibleData();
    QString roomId = QString::fromStdString(engine->getRoomsManager()->currentRoom()->id);
    if (current_room != roomId) {
        current_room = roomId;
        emit roomChanged();
    }
    for (GuiDataVect::iterator i = data.begin(); i != data.end(); ++i){
        GuiData data = (*i);
        engine->relToAbsRect(data.rect);
        if (data.text != "")
            emit drawText(QString::fromStdString(data.id), QString::fromStdString(data.text), data.rect.x, data.rect.y, data.rect.w, data.rect.h);
        if (data.image != "")
            emit drawImage(QString::fromStdString(data.id), QString::fromStdString(data.image), data.rect.x, data.rect.y, data.rect.w, data.rect.h, data.alpha/255.0);
    }
}

void Controller::click(float x, float y)
{
    std::pair<float, float> coord = engine->absToRelCoord(x, y);
    engine->click(coord.first, coord.second);
    if (int(engine->state()) != int(current_state)){
        current_state = Controller::State(engine->state());
        emit stateChanged();
    }
}
