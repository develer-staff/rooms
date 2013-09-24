#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "engine.h"

#include <QQuickPaintedItem>
#include <string>
#include <map>

using std::string;

class Graphics : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int t READ t WRITE setT NOTIFY tChanged)
public:
    explicit Graphics(QQuickPaintedItem *parent = 0);
    ~Graphics();

    void paint(QPainter *painter);

    int t() const {return _t;}
    void setT(int t);

signals:
    void tChanged();

public slots:
    void click(float x, float y);
    void mouseMove(float x, float y);

private slots:
    void updateSize();

private:
    QPixmap optimizedSetOpacity(QPixmap img, int opacity);
    void drawImage(QPainter *painter, string image, GuiRect rect, int alpha);
    void drawText(QPainter *painter, string text, GuiRect rect);
    void loadImages();

private:
    Engine *engine;
    std::map <string, QPixmap *> images;
    int _t;

};

#endif // GRAPHICS_H
