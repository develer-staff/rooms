#   ifndef ROOMSENGINE_H
#   define ROOMSENGINE_H

#include "DrawManager.h"

class RoomsEngine
{
    public:
        static RoomsEngine *CreateEngine();
        virtual ~RoomsEngine();
    protected:
    private:
        RoomsEngine();
        static RoomsEngine *_engine;

        DrawManager *_draw_mgr;

};

#endif // ROOMSENGINE_H
