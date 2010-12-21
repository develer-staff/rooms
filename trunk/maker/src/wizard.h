#ifndef WIZARD_H
#define WIZARD_H

#include <QDialog>

namespace Ui
{
    class Wizard;
}

class Wizard : public QDialog
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = 0);
    ~Wizard();
    QString worldName() const;
    QSize worldSize() const;

private slots:
    void setInfo();

private:
    Ui::Wizard *ui;
    QString name;
    int width;
    int height;
};

#endif // WIZARD_H
