#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
    connect(ui->createButton, SIGNAL(clicked()), this, SLOT(setInfo()));
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::setInfo()
{
    name = ui->worldName->text();
    width = ui->width->value();
    height = ui->height->value();
    close();
}

QString Wizard::getName() const
{
    return name;
}

QSize Wizard::getSize() const
{
    return QSize(width, height);
}
