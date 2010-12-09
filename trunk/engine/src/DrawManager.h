#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QtGui>
#include "DrawDevice.h"

class RoomsEngine;

class DrawManager
{
    public:
        DrawManager(RoomsEngine *engine);
        virtual ~DrawManager();

        void initApplication();
        int startApplication();
    protected:
    private:
        RoomsEngine *_engine;
        QApplication *_app;
        QMainWindow *_wnd;
        DrawDevice *_device;
};

#endif // DRAWMANAGER_H
