#include "RoomsEngine.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine(int argc, char *argv[])
{
    //ctor
    _draw_mgr = new DrawManager(this);
    _argc = argc;
    _argv = argv;
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _draw_mgr;
}

RoomsEngine *RoomsEngine::CreateEngine(int argc, char * argv[])
{
    if (_engine == 0)
    {
        _engine = new RoomsEngine(argc, argv);
    }
    return _engine;
}

int RoomsEngine::initialize()
{
    _draw_mgr->initApplication(_argc, _argv);
    return _draw_mgr->startApplication();
}
