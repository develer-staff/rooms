#include "engine.h"
#include "controller.h"
#include "qguidata.h"

#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QtQml>

Engine engine;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    if (!engine.loadWorldFromFile("world.rooms")){
        engine.getLogger()->write("Error loading world file", Log::ERROR);
        app.exit(1);
    }

    viewer.rootContext()->setContextProperty("gamePath", QDir::currentPath());

    qmlRegisterType<Controller>("rooms", 1, 0, "Controller");
    qmlRegisterType<QGuiData>("rooms", 1, 0, "GuiData");

    viewer.setMainQmlFile(QStringLiteral("qml/qml-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
