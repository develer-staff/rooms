#ifndef ROOMSENGINE_H
#define ROOMSENGINE_H

#include <QtGui>
#include <string> //std::string

#include "../lib/tinyxml/tinyxml.h"

class RoomsManager;

class RoomsEngine
{
    public:
        static RoomsEngine *CreateEngine();
        virtual ~RoomsEngine();
        int initialize();
        void click (int x, int y);
        bool loadWorld(std::string filename);
        void loadGame(std::string filename);

    protected:
    private:
        RoomsEngine();
        static RoomsEngine *_engine;

        RoomsManager *_rooms_mgr;
};

#endif // ROOMSENGINE_H
