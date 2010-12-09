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
        static RoomsEngine *_engine;
        DrawManager *_draw_mgr;

        RoomsEngine();
};

#endif // ROOMSENGINE_H
