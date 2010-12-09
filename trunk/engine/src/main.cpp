#include <QtGui>
#include "DrawDevice.h"
#include "RoomsEngine.h"

int main(int argc, char *argv[])
{
    QApplication qt_app(argc, argv);
    QMainWindow qt_wnd;
    RoomsEngine *eng = RoomsEngine::CreateEngine();
    eng->initialize();
    DrawDevice qt_draw_device(eng, &qt_wnd);
    qt_wnd.setCentralWidget(&qt_draw_device);
    qt_wnd.show();
    return qt_app.exec();
}
