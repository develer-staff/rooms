#include "graphics.h"
#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    qmlRegisterType<Graphics>("rooms", 1, 0, "GameView");

    viewer.setMainQmlFile(QStringLiteral("qml/qml-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
