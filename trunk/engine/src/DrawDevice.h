#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include <QtGui>
#include <map>
#include <string>
#include <fstream> //ifstream in fileExists()

class RoomsEngine;

class DrawDevice: public QWidget
{
    Q_OBJECT
    public:
        DrawDevice(RoomsEngine *engine, QWidget *parent=0);
        virtual ~DrawDevice();
    public:
        bool loadImage(std::string id, std::string filename);
    public slots:
        //QT EVENTS
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent * event);
    private:
        RoomsEngine *_engine;
        std::map <std::string, QImage *> _images;
        bool fileExists(std::string filename);
};

#endif // DRAWDEVICE_H
