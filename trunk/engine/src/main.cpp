#include "RoomsEngine.h"

int main()
{
    RoomsEngine *eng = RoomsEngine::CreateEngine();
    delete eng;
    return 0;
}
