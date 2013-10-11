#include "engine.h"
#include "controller.h"
#include "qguidata.h"

#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QtQml>
#include <QDebug>

Engine engine;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    QFile world_description("assets:/world.rooms");
    if (!world_description.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error: cannot open rooms file";
        app.exit(1);
    }
    QString descr_string(world_description.readAll());
    world_description.close();

    if (!engine.loadWorldFromStr(descr_string.toStdString())){
        qDebug() << "Error loading world";
        app.exit(1);
    }

    qmlRegisterType<Controller>("rooms", 1, 0, "Controller");
    qmlRegisterType<QGuiData>("rooms", 1, 0, "GuiData");

    viewer.setMainQmlFile(QStringLiteral("qml/android-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
