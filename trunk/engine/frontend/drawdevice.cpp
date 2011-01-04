#include "drawdevice.h"


DrawDevice::DrawDevice(Engine *eng, QWidget *parent): QWidget(parent)
{
    engine = eng;
    setGeometry(parent->geometry());
}

DrawDevice::~DrawDevice()
{
    for (std::map<string, QPixmap *>::iterator i = images.begin();
         i != images.end(); ++i)
    {
        delete i->second;
    }
    images.clear();
}

void DrawDevice::initialize()
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    hint_text.setParent(this);
    dialog_list.setParent(this);
    dialog_text.setParent(this);
    inventory_list.setParent(this);
    dialog_list.setFocusPolicy(Qt::NoFocus);
    dialog_text.setFocusPolicy(Qt::NoFocus);
    inventory_list.setFocusPolicy(Qt::NoFocus);
    hint_text.setFocusPolicy(Qt::NoFocus);
    hint_text.hide();
    dialog_list.hide();
    dialog_text.hide();
    inventory_list.hide();
    hint_text.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dialog_list.setStyleSheet("QListWidget {border-width: 4px;"
                              "border-style: solid;"
                              "border-radius: 10px;"
                              "border-color: white;}"
                              "QListWidget::item:hover {"
                              "background: rgba(0, 50, 255, 20%)}");
    hint_text.setStyleSheet("QLabel {border-width: 4px;"
                              "border-style: solid;"
                              "border-radius: 10px;"
                              "border-color: black;"
                              "background: rgba(220, 235, 255, 80%);}");
    dialog_text.setStyleSheet("QLabel {border-width: 4px;"
                              "border-style: solid;"
                              "border-radius: 10px;"
                              "border-color: white;"
                              "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
                              "stop:0 white, stop:0.4 rgba(10, 20, 30, 40), stop:1 "
                              "rgba(0, 200, 230, 200));}");
    inventory_list.setStyleSheet("QListWidget {border-width: 4px;"
                              "border-style: solid;"
                              "border-radius: 10px;"
                              "border-color: white;"
                              "background: rgba(200, 220, 255, 95%)}"
                              "QListWidget::item:hover {"
                              "background: rgba(190, 220, 250, 85%)}"
                              "QListWidget::item {"
                              "background: rgba(190, 216, 242, 80%)}");
    dialog_list.setGeometry(10, 410, width() - 20, 180);
    hint_text.setGeometry(20, height() - 60, width() - 40, 50);
    dialog_text.setGeometry(20, 350, width() - 40, 50);
    inventory_list.setGeometry(QRect(25, 25, width() - 50, height()- 50));
    std::vector<string> images = engine->getImgNames();
    for (std::vector<string>::iterator i = images.begin();
         i != images.end(); ++i)
         loadImage(*i);
    connect(&dialog_list, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(dialogChosed(QListWidgetItem *)));
}

bool DrawDevice::loadImage(string filename)
{
    if (fileExists(filename))
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

void DrawDevice::dialogChosed(QListWidgetItem *item)
{
    std::map<string, string> choices = engine->getDialogChoices();
    engine->clickDialog(choices[item->text().toStdString()]);
    update();
}

void DrawDevice::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawRoom(painter);
    switch (engine->state())
    {
        case Engine::GAME:
        {
            break;
        }
        default:
        {
            painter.fillRect(0, 0, width(), height(), QColor(0, 0, 0, 200));
            break;
        }
    }
}

void DrawDevice::mousePressEvent(QMouseEvent * event)
{
    if (engine->state() == Engine::GAME)
    {
        std::pair<float, float> coord = engine->absToRelCoord(event->x(), event->y());
        engine->clickArea(coord.first, coord.second);
        update();
    }
}

void DrawDevice::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        case Qt::Key_I:
        {
            if (engine->state() != Engine::INVENTORY)
            {
                before_inv_state = engine->state();
                engine->setState(Engine::INVENTORY);
            }
            else
                engine->setState(before_inv_state);
            setCursor(Qt::ArrowCursor);
            update();
            break;
        }
        default:
        {
            QWidget::keyPressEvent(event);
            break;
        }
    }
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
        {
            hint_text.setText(item->id.c_str());
            hint_text.show();
        }
        else
            hint_text.hide();

        if (item != 0)
            setCursor(Qt::OpenHandCursor);
        else if (area != 0)
            setCursor(Qt::PointingHandCursor);
        else
            setCursor(Qt::ArrowCursor);

        update();
    }
}

void DrawDevice::resizeEvent(QResizeEvent *event)
{
    engine->getRoomsManager()->size(event->size().width(), event->size().height());
}

void DrawDevice::update()
{
    if (engine->state() == Engine::DIALOG)
    {
        setCursor(Qt::ArrowCursor);
        std::map<string, string> choices = engine->getDialogChoices();
        string text = engine->getDialogText();
        dialog_list.clear();
        dialog_text.setText("<font color=#FFFFFF>" + QString::fromUtf8(text.c_str()) + "</font>");
        for (std::map<string, string>::iterator i = choices.begin();
             i != choices.end(); ++i)
            dialog_list.addItem(QString::fromUtf8(i->first.c_str()));
        dialog_list.show();
        dialog_text.show();
    }

    if (engine->state() == Engine::INVENTORY)
    {
        setCursor(Qt::ArrowCursor);
        std::vector<Item *> items = engine->getInventory();
        inventory_list.clear();
        for (std::vector<Item *>::iterator i = items.begin();
             i != items.end(); ++i)
        {
            QPixmap *img = images[(*i)->image()];
            QListWidgetItem *itm = new QListWidgetItem(tr((*i)->id.c_str()));
            itm->setIcon(QIcon(*img));
            inventory_list.addItem(itm);
        }
        inventory_list.show();
    }
    else
        inventory_list.hide();

    if (engine->state() == Engine::GAME)
    {
        dialog_text.hide();
        dialog_list.hide();
    }

    QWidget::update();
}

void DrawDevice::drawRoom(QPainter &painter)
{
    //Draw room
    Room *room = engine->getRoomsManager()->currentRoom();
    QPixmap *bg = images[room->bg()];
    QRect rect(0, 0, width(), height());
    std::vector <Item *> items = room->items();
    painter.drawPixmap(rect, *bg);
    //Draw items
    for (std::vector<Item *>::iterator i = items.begin();
         i != items.end(); ++i)
    {
        std::pair<int, int> point = engine->relToAbsCoord((*i)->x(), (*i)->y());
        std::pair<int, int> size = engine->relToAbsCoord((*i)->w(), (*i)->h());;
        painter.drawPixmap(QRect(point.first, point.second,
                                 size.first, size.second), *images[(*i)->image()]);
    }
}

