#include "../src/engine.h"
#include "drawdevice.h"

#include <QtGui>

int main(int argc, char *argv[])
{
    Engine *eng = new Engine;
    if (!eng->loadWorldFromFile("world.rooms"))
    {
        eng->getLogger()->write("ERROR: cannot load world.rooms!", Log::ERROR);
        delete eng;
        return 1;
    }
    QApplication qt_app(argc, argv);
    QFile file("style.qss");
    if (file.exists())
    {
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        qt_app.setStyleSheet(styleSheet);
    }
    QMainWindow qt_wnd;
    RoomsManager *man = eng->getRoomsManager();
    qt_wnd.setBaseSize(man->width(), man->height());
    qt_wnd.setWindowTitle(man->name().c_str());
    DrawDevice qt_draw_device(eng, &qt_wnd);
    qt_draw_device.initialize();
    qt_wnd.setCentralWidget(&qt_draw_device);
    qt_wnd.show();
    int r = qt_app.exec();
    delete eng;
    return r;
}
