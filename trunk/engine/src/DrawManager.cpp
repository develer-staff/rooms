#include "DrawManager.h"

DrawManager::DrawManager(RoomsEngine *engine)
{
    //ctor
    _engine = engine;
}

DrawManager::~DrawManager()
{
    //dtor
    delete _device;
    delete _wnd;
    delete _app;
}

void DrawManager::initApplication()
{
    char *argv[1] = {"rooms"};
    int argc = 1;
    _app = new QApplication(argc, argv);
    _wnd = new QMainWindow;
    _device = new DrawDevice();
    _wnd->setCentralWidget(_device);
    _wnd->setWindowTitle("Rooms Engine");
    _wnd->resize(800, 600);
    _wnd->show();
}


int DrawManager::startApplication()
{
    return _app->exec();
}

