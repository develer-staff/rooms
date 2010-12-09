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

void DrawManager::initApplication(int argc, char *argv[])
{
    _app = new QApplication(argc, argv);
    _wnd = new QMainWindow;
    _device = new DrawDevice(_wnd);
    _wnd->setCentralWidget(_device);
    _wnd->show();
    //_device->resize(800,600);
}


int DrawManager::startApplication()
{
    return _app->exec();
}

