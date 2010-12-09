#include "RoomsEngine.h"
#include "DrawManager.h"
#include "RoomsManager.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine(int argc, char *argv[])
{
    //ctor
    _draw_mgr = new DrawManager(this);
    _rooms_mgr = new RoomsManager(this);
    _argc = argc;
    _argv = argv;
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _draw_mgr;
    delete _rooms_mgr;
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

void RoomsEngine::click (int x, int y)
{

}


void RoomsEngine::loadGame(std::string filename)
{

}

void RoomsEngine::loadWorld(std::string filename)
{
    TiXmlDocument document(filename.c_str());
    document.LoadFile();

    //STUB

    Room *r = _rooms_mgr->addRoom("prova1");
}
