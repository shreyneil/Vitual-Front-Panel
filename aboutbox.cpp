#include "aboutbox.h"
#include "ui_aboutbox.h"
#include "utils.h"
AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
}

AboutBox::~AboutBox()
{
    Utils::DestructorMsg(this);
    delete ui;
}
