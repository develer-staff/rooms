#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QtGui>

class DrawDevice: public QWidget
{
    Q_OBJECT
    public:
        DrawDevice(QWidget *parent=0);
        //virtual ~DrawDevice();
    private slots:
        //QT EVENTS
        void paintEvent(QPaintEvent *event);
};

#endif // DRAWDEVICE_H
