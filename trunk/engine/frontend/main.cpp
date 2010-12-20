#include "../src/engine.h"
#include "drawdevice.h"

#include <QtGui>

int main(int argc, char *argv[])
{
    Engine *eng = Engine::createEngine();
    if (!eng->loadWorld("world.rooms"))
    {
        eng->getLogger()->write("ERROR: cannot load world.rooms!", Log::ERROR);
        eng->exit();
        return 1;
    }
    QApplication qt_app(argc, argv);
    QMainWindow qt_wnd;
    RoomsManager *man = eng->getRoomsManager();
    qt_wnd.resize(man->width(), man->height());
    qt_wnd.setWindowTitle(man->name().c_str());
    DrawDevice qt_draw_device(eng, &qt_wnd);
    qt_draw_device.initialize();
    qt_wnd.setCentralWidget(&qt_draw_device);
    qt_wnd.show();
    int r = qt_app.exec();
    eng->exit();
    return r;
}
