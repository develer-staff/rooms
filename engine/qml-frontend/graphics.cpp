#include <QtQuick/qquickwindow.h>
#include <QPainter>

#include "graphics.h"

Graphics::Graphics(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),
    _t(0)
{
    engine = new Engine();
    if (!engine->loadWorldFromFile("world.rooms")) {
        engine->getRoomsManager()->setRoomSize(0,0);
    }
    loadImages();
    setAntialiasing(true);
    connect(this, SIGNAL(widthChanged()), this, SLOT(updateSize()));
    connect(this, SIGNAL(heightChanged()), this, SLOT(updateSize()));
    connect(this, SIGNAL(tChanged()), this, SLOT(update()));
}

Graphics::~Graphics()
{
    delete engine;
}

void Graphics::paint(QPainter *painter)
{
    if (engine) {
        GuiDataVect data = engine->getVisibleData();
        for (GuiDataVect::iterator i = data.begin(); i != data.end(); ++i){
            GuiData data = (*i);
            engine->relToAbsRect(data.rect);
            if (data.image != "")
                drawImage(painter, data.image, data.rect, data.alpha);
            if (data.text != "")
                drawText(painter, data.text, data.rect);
        }
    }
}

void Graphics::setT(int t)
{
    if (_t == t)
        return;
    _t = t;
    emit tChanged();
}

void Graphics::click(float x, float y)
{
    std::pair<float, float> coord = engine->absToRelCoord(x, y);
    engine->click(coord.first, coord.second);
}

void Graphics::mouseMove(float x, float y)
{
    if (engine->state() == Engine::GAME)
    {
        std::pair<float, float> coord = engine->absToRelCoord(x, y);
        Item *item = engine->getRoomsManager()->currentRoom()->itemAt(coord.first,
                                                                    coord.second);
        Area *area = engine->getRoomsManager()->currentRoom()->areaAt(coord.first,
                                                                    coord.second);
        if (item != 0)
            setCursor(Qt::OpenHandCursor);
        else if (area != 0)
            setCursor(Qt::PointingHandCursor);
        else
            setCursor(Qt::ArrowCursor);
    }
    else
        setCursor(Qt::ArrowCursor);
}

void Graphics::updateSize()
{
    engine->getRoomsManager()->setRoomSize(width(), height());
}

QPixmap Graphics::optimizedSetOpacity(QPixmap img, int opacity)
{
    QPixmap temp(img.size());
    temp.fill(Qt::transparent);
    QPainter p(&temp);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, img);
    QLinearGradient alpha_gradient(0, 0, img.width(), 0);
    alpha_gradient.setColorAt(0, QColor(255, 255, 255, opacity));
    alpha_gradient.setColorAt(1, QColor(255, 255, 255, opacity));
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.setBrush(alpha_gradient);
    p.drawRect(0, 0, temp.width(), temp.height());
    p.end();
    return temp;
}

void Graphics::drawImage(QPainter *painter, std::string image, GuiRect rect, int alpha)
{
    QPixmap p = *images[image];
    painter->drawPixmap(rect.x, rect.y, rect.w, rect.h, optimizedSetOpacity(p, alpha));
}

void Graphics::drawText(QPainter *painter, std::string text, GuiRect rect)
{
    int x = rect.x;
    int y = rect.y + rect.h / 2;
    painter->drawText(x, y, QString::fromUtf8(text.c_str()));
}

void Graphics::loadImages()
{
    std::vector<string> names = engine->getImgNames();
    for (std::vector<string>::iterator i = names.begin(); i != names.end(); ++i) {
        if (QFile::exists(QString::fromStdString((*i))))
            images[(*i)] = new QPixmap((*i).c_str());
    }
}
