#include <QtGui>
#include "drawdevice.h"
#include "roomsengine.h"

int main(int argc, char *argv[])
{
    QApplication qt_app(argc, argv);
    QMainWindow qt_wnd;
    RoomsEngine *eng = RoomsEngine::createEngine();
    DrawDevice qt_draw_device(eng, &qt_wnd);
    eng->setDevice(&qt_draw_device);
    eng->initialize();
    qt_draw_device.initialize();
    qt_wnd.setCentralWidget(&qt_draw_device);
    qt_wnd.show();
    return qt_app.exec();
}
