#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QtGui>

class DrawDevice;
class RoomsEngine;

class DrawManager
{
    public:
        DrawManager(RoomsEngine *engine);
        virtual ~DrawManager();

        void initApplication(int argc, char *argv[]);
        int startApplication();

        void click(int x, int y);
    protected:
    private:
        RoomsEngine *_engine;
        QApplication *_app;
        QMainWindow *_wnd;
        DrawDevice *_device;
};

#endif // DRAWMANAGER_H
