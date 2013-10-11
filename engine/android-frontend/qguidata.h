#ifndef QGUIDATA_H
#define QGUIDATA_H

#include <QObject>

class QGuiData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(float x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(float y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(float alpha READ alpha WRITE setAlpha NOTIFY alphaChanged)
public:
    explicit QGuiData(QObject *parent = 0);

    QString content() const;
    void setContent(const QString &content);

    QString id() const;
    void setId(const QString &id);

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

    float width() const;
    void setWidth(float width);

    float height() const;
    void setHeight(float height);

    float alpha() const;
    void setAlpha(float alpha);

    void setTextFlag();
    Q_INVOKABLE bool isText() const;

signals:
    void contentChanged();
    void idChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void alphaChanged();

private:
    QString _content;
    QString _id;
    float _x;
    float _y;
    float _width;
    float _height;
    float _alpha;
    bool _text;

};

#endif // QGUIDATA_H
