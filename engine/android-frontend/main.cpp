#include "engine.h"
#include "controller.h"
#include "qguidata.h"

#include "qtquick2applicationviewer.h"

#include <QtGui/QGuiApplication>
#include <QXmlStreamReader>
#include <QtQml>
#include <QDebug>

Engine engine;


// This workaround is needed because Rooms engine cannot read
// from Android assets pseudo-folder
void preloadCutscene(const QString &worldContent){
    QXmlStreamReader xml(worldContent);
    QStringList csList;
    while(!xml.atEnd()){
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartDocument)
            continue;

        if (token == QXmlStreamReader::StartElement){
            if (xml.name() == "action" && xml.attributes().value("id") == "CUTSCENE_START"){
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "action")){
                    xml.readNext();
                    if (xml.name() != "param")
                        continue;
                    QString csPath = xml.attributes().value("value").toString();
                    QFile csFile(csPath);
                    if (!csFile.exists()){
                        if (QFile::copy(QString("assets:/%1").arg(csPath), csPath))
                            csList.append(csPath);
                    }
                }
            }
        }
    }

    QRegExp rx("###[^\"]+\"([^\"]+)\"");
    foreach (const QString &f, csList){
        QFile file(f);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString txt = file.readAll();
        file.close();
        if(rx.indexIn(txt) != -1){
            QFile csdFile(rx.cap(1));
            if (!csdFile.exists()) {
                qDebug() << rx.cap(1);
                QFile::copy(QString("assets:/%1").arg(rx.cap(1)), rx.cap(1));
            }
        }
    }
}

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

    preloadCutscene(descr_string);

    qmlRegisterType<Controller>("rooms", 1, 0, "Controller");
    qmlRegisterType<QGuiData>("rooms", 1, 0, "GuiData");

    viewer.setMainQmlFile(QStringLiteral("qml/android-frontend/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
