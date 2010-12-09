#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QtGui>

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
        //QT INTERFACE
        QApplication *_app;
        QMainWindow *_wnd;
};

#endif // DRAWMANAGER_H
