#include "qguidata.h"

QGuiData::QGuiData(QObject *parent) :
    QObject(parent),
    _text(false)
{
}

QString QGuiData::content() const
{
    return _content;
}

void QGuiData::setContent(const QString &content)
{
    if (_content == content)
        return;
    _content = content;
    emit contentChanged();
}

QString QGuiData::id() const
{
    return _id;
}

void QGuiData::setId(const QString &id)
{
    if (_id == id)
        return;
    _id = id;
    emit idChanged();
}

float QGuiData::x() const
{
    return _x;
}

void QGuiData::setX(float x)
{
    _x = x;
    emit xChanged();
}

float QGuiData::y() const
{
    return _y;
}

void QGuiData::setY(float y)
{
    _y = y;
    emit yChanged();
}

float QGuiData::width() const
{
    return _width;
}

void QGuiData::setWidth(float width)
{
    _width = width;
    emit widthChanged();
}

float QGuiData::height() const
{
    return _height;
}

void QGuiData::setHeight(float height)
{
    _height = height;
    emit heightChanged();
}

float QGuiData::alpha() const
{
    return _alpha;
}

void QGuiData::setAlpha(float alpha)
{
    _alpha = alpha;
    emit alphaChanged();
}

void QGuiData::setTextFlag()
{
    _text = true;
}

bool QGuiData::isText() const
{
    return _text;
}
