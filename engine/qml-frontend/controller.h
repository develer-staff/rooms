#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "engine.h"
#include "qguidata.h"

#include <QObject>
#include <QList>
#include <QQmlListProperty>

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int windowWidth READ windowWidth WRITE setWindowWidth NOTIFY windowWidthChanged)
    Q_PROPERTY(int windowHeight READ windowHeight WRITE setWindowHeight NOTIFY windowHeightChanged)
    Q_PROPERTY(int t READ t WRITE setT NOTIFY tChanged)
    Q_PROPERTY(QString room READ room NOTIFY roomChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QQmlListProperty<QGuiData> currentFrame READ currentFrame NOTIFY currentFrameChanged)
    Q_ENUMS(State)
public:

    enum State {
        INITIALIZING = Engine::INITIALIZING,
        GAME = Engine::GAME,
        DIALOG = Engine::DIALOG,
        TRANSITION = Engine::TRANSITION
    };

    explicit Controller(QObject *parent = 0);
    ~Controller();

    int windowWidth() const;
    void setWindowWidth(int width);

    int windowHeight() const;
    void setWindowHeight(int height);

    int t() const {return _t;}
    void setT(int t);

    QString room() const;

    State state() const;

    QQmlListProperty<QGuiData> currentFrame();

    static int listCount(QQmlListProperty<QGuiData> *list);
    static QGuiData *listAt(QQmlListProperty<QGuiData> *list, int index);

signals:
    void windowWidthChanged();
    void windowHeightChanged();
    void tChanged();
    void roomChanged();
    void stateChanged();
    void currentFrameChanged();

public slots:
    void update();
    void click(float x, float y);

private:
    void clearCurrentFrameData();

private:
    int _t;
    QString current_room;
    Engine *engine;
    State current_state;
    QList<QGuiData *> _currentFrameData;
};

#endif // CONTROLLER_H
