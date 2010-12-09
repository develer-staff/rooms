#include "RoomsEngine.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _draw_mgr = new DrawManager();
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
