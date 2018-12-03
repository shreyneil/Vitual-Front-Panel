#pragma once
#include <QObject>

class IntSocket;
class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent, IntSocket& sock);
    virtual ~Instrument();
    void Connect();
    void DisConnect() const;
    bool IsConnected() const;
    QString GetHostName() const;
    quint16 GetPort() const;
    void SetLongWaitMS(int value);
    void SetShortWaitMS(int value);
    //we need to notify the outside world about certain events using our signals.

signals:
    void NotifyConnected()const;
    void NotifyDisConnected()const;
    void NotifyDataSent(const QString& datasent) const;
    void NotifyDataReceived(const QString& readData)const;
    void NotifyErrorDetected(const QString& errorMsg)const;
    void NotifyStatusUpdated(const QString& statusMsg)const;
public slots:
    void onHostNameChanged(const QString& hostName);
    void onPortChanged(quint16 port);
    void onConnected();
    void onDisConnected();
    void onSendRequest(const QString& dataToSend);
    void onReceiveRequest();
    void onPulseWidthChange(double value);


private:
    IntSocket& m_intSocket;
    QString m_lastCommandSent;
    void WireConnections();
    //For wiring up the signals from sockets to our slots.
    explicit Instrument(const Instrument& rhs) = delete;
    Instrument& operator= (const Instrument& rhs) = delete;
};



