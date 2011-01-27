#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include "../src/engine.h"

#include <QtGui> //QWidget, QImage
#include <map> //std::map
#include <string> //std::string
#include <fstream> //ifstream in fileExists()
#include <utility> //std::pair

using std::string;

namespace
{
    bool fileExists(string filename)
    {
        std::ifstream ifile(filename.c_str());
        return ifile;
    }
}

/*! \brief Graphic interface class.
 *         It handles user event and it controls engine.
 */
class DrawDevice: public QWidget
{
    Q_OBJECT
    private:
        Engine *engine;
        std::map <string, QPixmap *> images;
        QString last_bgm;
        QSound *bgm;
    public:
        DrawDevice(Engine *eng, QWidget *parent=0);
        ~DrawDevice();
    public:
        void initialize();
        bool loadImage(string filename);
        void quit(int status);
        void drawImage(QPainter &painter, string name, GuiRect rect);
        void drawText(QPainter &painter, string text, GuiRect rect);
        void drawRoom(QPainter &painter);
        void updateMusic();
    public slots:
        //QT EVENTS
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent *event);
        void resizeEvent(QResizeEvent *event);
};

#endif // DRAWDEVICE_H
