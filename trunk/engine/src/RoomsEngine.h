#   ifndef ROOMSENGINE_H
#   define ROOMSENGINE_H

#include "DrawManager.h"

class RoomsEngine
{
    public:
        static RoomsEngine *CreateEngine(int argc, char *argv[]);
        virtual ~RoomsEngine();
        int initialize();
    protected:
    private:
        RoomsEngine(int argc, char *argv[]);
        static RoomsEngine *_engine;

        int _argc;
        char **_argv;

        DrawManager *_draw_mgr;
};

#endif // ROOMSENGINE_H
