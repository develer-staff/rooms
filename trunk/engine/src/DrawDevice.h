#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QtGui>

class DrawManager;

class DrawDevice: public QWidget
{
    Q_OBJECT
    public:
        DrawDevice(DrawManager *manager, QWidget *parent=0);
    public slots:
        //QT EVENTS
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent * event);
    private:
        DrawManager *_manager;
};

#endif // DRAWDEVICE_H
