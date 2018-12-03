#ifndef SETUPTAB_H
#define SETUPTAB_H

#include <QWidget>

class QStringListModel;
namespace Ui {
class SetupTab;
}

class SetupTab : public QWidget
{
    Q_OBJECT

public:
    explicit SetupTab(QWidget *parent = 0);
    ~SetupTab();

    void SetHostName(const QString &value);
    void SetPort(quint16 value);
    void SetCommands(QStringListModel& commands);
signals:
    void NotifyHostNameChanged(const QString& value);
    void NotifyPortNameChanged(quint16 value);
    void NotifyConnectClicked();
    void NotifyDisconnectClicked();
    void NotifySendClicked(const QString& dataTosend);
    void NotifyReceivedClicked();
public slots:
    void onStatusUpdated(const QString& statusMsg);
    void onConnected();
    void onDisconnect();
    void onDataSent(const QString& dataSent);
    void onDataReceived(const QString& dataRead);
    void onConnectEnabled(bool isEnabled);
    void onDisconnectEnabled(bool isEnabled);
    void onDirectCommandsEnabled(bool isEnabled);
    void onControlTabEnabled(bool isEnabled);
private slots:
    void on_EditIP_editingFinished();

    void on_EditPort_editingFinished();

    void on_btnConnect_clicked();

    void on_btnDisconnect_clicked();

    void on_btnSend_clicked();

    void on_btnReceive_clicked();

    void on_btnClear_clicked();

private:
    Ui::SetupTab *ui;
};

#endif // SETUPTAB_H
