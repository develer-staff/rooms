#include "controller.h"

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

QQmlListProperty<QGuiData> Controller::currentFrame()
{
    return QQmlListProperty<QGuiData>(this, 0, &Controller::listCount, &Controller::listAt);
}

int Controller::listCount(QQmlListProperty<QGuiData> *list)
{
    Controller *c = qobject_cast<Controller *>(list->object);
    return c->_currentFrameData.size();
}

QGuiData *Controller::listAt(QQmlListProperty<QGuiData> *list, int index)
{
    Controller *c = qobject_cast<Controller *>(list->object);
    return c->_currentFrameData.at(index);
}

void Controller::update()
{
    GuiDataVect data = engine->getVisibleData();
    clearCurrentFrameData();
    QString roomId = QString::fromStdString(engine->getRoomsManager()->currentRoom()->id);
    if (current_room != roomId) {
        current_room = roomId;
        emit roomChanged();
    }
    for (GuiDataVect::iterator i = data.begin(); i != data.end(); ++i){
        GuiData data = (*i);
        engine->relToAbsRect(data.rect);
        QGuiData *d = new QGuiData();
        d->setX(data.rect.x);
        d->setY(data.rect.y);
        d->setWidth(data.rect.w);
        d->setHeight(data.rect.h);
        d->setAlpha(data.alpha/255.0);
        d->setId(QString::fromStdString(data.id));
        if (data.text != ""){
            d->setTextFlag();
            d->setContent(QString::fromStdString(data.text));
        } else if (data.image != ""){
            d->setContent(QString::fromStdString(data.image));
        } else {
            continue; //inventory_label non ha ne testo ne immagine
        }
        _currentFrameData.append(d);
    }
    emit currentFrameChanged();
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

void Controller::clearCurrentFrameData()
{
    while(_currentFrameData.length() > 0){
        delete _currentFrameData.takeLast();
    }
}
