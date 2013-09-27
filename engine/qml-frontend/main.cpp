#include "controller.h"
#include "qguidata.h"

#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;

    viewer.rootContext()->setContextProperty("gamePath", QDir::currentPath());

    qmlRegisterType<Controller>("rooms", 1, 0, "Controller");
    qmlRegisterType<QGuiData>("rooms", 1, 0, "GuiData");

    viewer.setMainQmlFile(QStringLiteral("qml/qml-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
