#include "drawdevice.h"

#include <QFile>

DrawDevice::DrawDevice(Engine *eng, QWidget *parent) : QWidget(parent)
{
    engine = eng;
    setGeometry(parent->geometry());
    bgm = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateEngine()));
    timer->start(1000/25);
}

DrawDevice::~DrawDevice()
{
    for (std::map<string, QPixmap *>::iterator i = images.begin();
            i != images.end(); ++i)
    {
        delete i->second;
    }
    images.clear();
    if (bgm) delete bgm;
    delete timer;
}

void DrawDevice::initialize()
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    std::vector<string> images = engine->getImgNames();
    for (std::vector<string>::iterator i = images.begin();
            i != images.end(); ++i)
        loadImage(*i);
}

bool DrawDevice::loadImage(string filename)
{
    if (QFile::exists(QString::fromStdString(filename)))
    {
        images[filename] = new QPixmap(filename.c_str());
        return true;
    }
    else
    {
        return false;
    }
}

void DrawDevice::quit(int status)
{
    qApp->exit(status);
}

void DrawDevice::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawRoom(painter);
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    std::pair<float, float> coord = engine->absToRelCoord(event->x(), event->y());
    engine->click(coord.first, coord.second);
    update();
    updateMusic();
}

void DrawDevice::mouseMoveEvent(QMouseEvent *event)
{
    if (engine->state() == Engine::GAME)
    {
        std::pair<float, float> coord = engine->absToRelCoord(event->x(), event->y());
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

void DrawDevice::resizeEvent(QResizeEvent *event)
{
    engine->getRoomsManager()->setRoomSize(event->size().width(), event->size().height());
}

void DrawDevice::updateEngine()
{
    if (engine->update())
        repaint();
}

QPixmap optimizedSetOpacity(QPixmap img, int opacity)
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

void DrawDevice::drawImage(QPainter &painter, string name, GuiRect rect, int opacity)
{
    QPixmap img = *images[name];
    QRect r(rect.x, rect.y, rect.w, rect.h);
    painter.drawPixmap(r, optimizedSetOpacity(img, opacity));
}

void DrawDevice::drawText(QPainter &painter, string text, GuiRect rect)
{
    int x = rect.x;
    int y = rect.y + rect.h / 2;
    painter.drawText(x, y, QString::fromUtf8(text.c_str()));
}

void DrawDevice::drawRoom(QPainter &painter)
{
    GuiDataVect dv = engine->getVisibleData();
    for (GuiDataVect::iterator i = dv.begin(); i != dv.end(); ++i)
    {
        GuiData data = (*i);
        engine->relToAbsRect(data.rect);
        if (data.image != "")
            drawImage(painter, data.image, data.rect, data.alpha);
        if (data.text != "")
            drawText(painter, data.text, data.rect);
    }
}

void DrawDevice::updateMusic()
{
    // Background Music
    if (!QSound::isAvailable()) return;
    QString bgm_to_play(engine->getRoomsManager()->currentRoom()->bgm().c_str());
    if (bgm_to_play != "" && bgm_to_play != last_bgm)
    {
        if (bgm) delete bgm;
        bgm = new QSound(bgm_to_play);
        last_bgm = bgm_to_play;
    }
    if (bgm_to_play == "" && bgm) delete bgm;

    // SFX
    std::vector<string> sfx = engine->getSFX();
    for (std::vector<string>::iterator i = sfx.begin(); i != sfx.end(); ++i)
        QSound::play((*i).c_str());
}

