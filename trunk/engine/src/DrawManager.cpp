#include "DrawManager.h"
#include "RoomsEngine.h"

DrawManager::DrawManager(RoomsEngine *engine)
{
    //ctor
    _engine = engine;
}

DrawManager::~DrawManager()
{
    //dtor
}

void DrawManager::click(int x, int y)
{
    _engine->click(x, y);
}
