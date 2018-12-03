#include "controltab.h"
#include "ui_controltab.h"
#include "utils.h"

ControlTab::ControlTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlTab)
{
    ui->setupUi(this);
    Utils::DestructorMsg(this);
}

ControlTab::~ControlTab()
{
    delete ui;
}

void ControlTab::EnablePanel(bool isEnabled)
{
    ui->ControlTabPannel->setEnabled(isEnabled);
}

void ControlTab::on_spinPulseWidth_valueChanged(double value)
{
    emit NotifyPulseWidthChanged(value);
}
