#include "controller.h"
#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    qmlRegisterType<Controller>("rooms", 1, 0, "Controller");

    viewer.setMainQmlFile(QStringLiteral("qml/qml-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
