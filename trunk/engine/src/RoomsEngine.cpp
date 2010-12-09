#include "RoomsEngine.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _draw_mgr = new DrawManager(this);
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _draw_mgr;
}

RoomsEngine *RoomsEngine::CreateEngine()
{
    if (_engine == 0)
    {
        _engine = new RoomsEngine();
    }
    return _engine;
}

int RoomsEngine::initialize()
{
    _draw_mgr->initApplication();
    return _draw_mgr->startApplication();
}
