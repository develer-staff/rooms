#include "RoomsEngine.h"

#include <QtGui>

int main()
{
    RoomsEngine *eng = RoomsEngine::CreateEngine();
    eng->initialize();
    delete eng;

    return 0;
}
