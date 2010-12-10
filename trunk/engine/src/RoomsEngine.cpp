#include "RoomsEngine.h"
#include "RoomsManager.h"
#include <iostream>

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _rooms_mgr = new RoomsManager(this);
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _rooms_mgr;
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
    if (!loadWorld("test_world.rooms"))
        throw;  //TODO: handle exception
}

void RoomsEngine::click (int x, int y)
{

}


void RoomsEngine::loadGame(std::string filename)
{

}

bool RoomsEngine::loadWorld(std::string filename)
{
    TiXmlDocument document(filename.c_str());
    bool ok = document.LoadFile();
    if (ok)
    {
        TiXmlElement *root = document.RootElement();
        //TODO: read world file and build model
        return true;
    } else {
        return false;
    }
}
