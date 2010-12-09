#include "RoomsEngine.h"

int main(int argc, char *argv[])
{
    RoomsEngine *eng = RoomsEngine::CreateEngine(argc, argv);
    eng->initialize();
    delete eng;

    return 0;
}
