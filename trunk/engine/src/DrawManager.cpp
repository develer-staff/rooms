#include "DrawManager.h"

DrawManager::DrawManager(RoomsEngine *engine)
{
    //ctor
    _engine = engine;
}

DrawManager::~DrawManager()
{
    //dtor
    delete _wnd;
    delete _app;
}

void DrawManager::initApplication()
{
    char *argv[1] = {"rooms"};
    int argc = 1;
    _app = new QApplication(argc, argv);
    _wnd = new QMainWindow;
    _wnd->show();
}


int DrawManager::startApplication()
{
    return _app->exec();
}
