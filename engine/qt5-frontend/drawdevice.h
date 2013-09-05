#ifndef DRAWDEVICE_H
#define DRAWDEVICE_H

#include "engine.h"

#include <QtWidgets> //QWidget, QImage
#include <QSound>
#include <map> //std::map
#include <string> //std::string
#include <utility> //std::pair

using std::string;

/*! \brief Graphic interface class.
 *         It handles user event and it controls engine.
 */
class DrawDevice : public QWidget
{
    Q_OBJECT
private:
    Engine *engine;
    std::map <string, QPixmap *> images;
    QString last_bgm;
    QSound *bgm;
    QTimer *timer;
public:
    DrawDevice(Engine *eng, QWidget *parent = 0);
    ~DrawDevice();
public:
    void initialize();
    bool loadImage(string filename);
    void quit(int status);
    void drawImage(QPainter &painter, string name, GuiRect rect, int opacity = 255);
    void drawText(QPainter &painter, string text, GuiRect rect);
    void drawRoom(QPainter &painter);
    void updateMusic();
public slots:
    //QT EVENTS
    void updateEngine();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // DRAWDEVICE_H
