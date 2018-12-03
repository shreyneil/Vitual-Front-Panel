#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"
#include <QStringListModel>

SetupTab::SetupTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupTab)
{
    ui->setupUi(this);
}

SetupTab::~SetupTab()
{
    Utils::DestructorMsg(this);
    delete ui;
}

void SetupTab::SetHostName(const QString& value)
{
    ui->EditIP->setText(value);
    emit NotifyHostNameChanged(value);
}

void SetupTab::SetPort(quint16 value)
{
    ui->EditPort->setText(QString::number(value));
    emit NotifyPortNameChanged(value);
}

void SetupTab::SetCommands(QStringListModel &commands)
{
    ui->cbCommands->setModel(&commands);
}

void SetupTab::onStatusUpdated(const QString &statusMsg)
{
    ui->textInstrumentMessages->append(statusMsg);
}

void SetupTab::onConnected()
{
    auto connect_msg = QString(tr("Connected"));
    ui->textInstrumentMessages->append(connect_msg);
}

void SetupTab::onDisconnect()
{
    auto Disconnect_msg = QString(tr("Disconnected"));
    ui->textInstrumentMessages->append(Disconnect_msg);

}

void SetupTab::onDataSent(const QString &dataSent)
{
   ui->textInstrumentMessages->append("Data Sent. " + dataSent);
}

void SetupTab::onDataReceived(const QString &dataRead)
{
    ui->textInstrumentMessages->append(dataRead);
}

void SetupTab::onConnectEnabled(bool isEnabled)
{
    ui->btnConnect->setEnabled(isEnabled);
}

void SetupTab::onDisconnectEnabled(bool isEnabled)
{
    ui->btnDisconnect->setEnabled(isEnabled);
}

void SetupTab::onDirectCommandsEnabled(bool isEnabled)
{
    ui->gbDirectCommands->setEnabled(isEnabled);
}

void SetupTab::onControlTabEnabled(bool isEnabled)
{
  //TODO during control tab building
}

void SetupTab::on_EditIP_editingFinished()
{
    emit NotifyHostNameChanged(ui->EditIP->text());
}

void SetupTab::on_EditPort_editingFinished()
{
    bool ok;
    int result = ui->EditPort->text().toInt(&ok);
    if(!ok||(result>>USHRT_MAX))
    {
        ui->textInstrumentMessages->append(tr("Invalid Port Number" + result));
    }
    else
    {
    emit NotifyPortNameChanged(result);

    }
}

void SetupTab::on_btnConnect_clicked()
{
  emit NotifyConnectClicked();
}

void SetupTab::on_btnDisconnect_clicked()
{
  emit NotifyDisconnectClicked();
}

void SetupTab::on_btnSend_clicked()
{
  emit NotifySendClicked(ui->cbCommands->currentText());
}

void SetupTab::on_btnReceive_clicked()
{
  emit NotifyReceivedClicked();
}

void SetupTab::on_btnClear_clicked()
{
    ui->textInstrumentMessages->clear();
}
