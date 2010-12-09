#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

class RoomsEngine;

class DrawManager
{
    public:
        DrawManager(RoomsEngine *engine);
        virtual ~DrawManager();
        void click(int x, int y);
    protected:
    private:
        RoomsEngine *_engine;
};

#endif // DRAWMANAGER_H
