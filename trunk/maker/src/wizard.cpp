#include "wizard.h"
#include "ui_wizard.h"

Wizard::Wizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
    width = 600;
    height = 500;
    name = "Example world";
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setInfo()));
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
    accepted();
    close();
    ui->worldName->setText("Example world");
    ui->width->setValue(600);
    ui->height->setValue(500);
}

QString Wizard::worldName() const
{
    return name;
}

QSize Wizard::worldSize() const
{
    return QSize(width, height);
}
