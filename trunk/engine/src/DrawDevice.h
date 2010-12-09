#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QtGui>

class RoomsEngine;

class DrawDevice: public QWidget
{
    Q_OBJECT
    public:
        DrawDevice(DrawManager *engine, QWidget *parent=0);
    public slots:
        //QT EVENTS
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent * event);
    private:
        RoomsEngine *_engine;
};

#endif // DRAWDEVICE_H
