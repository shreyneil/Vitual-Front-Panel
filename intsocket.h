#pragma once
#include <QObject>

class QTcpSocket;

class IntSocket : public QObject
{
    Q_OBJECT
public:
    explicit IntSocket(QObject *parent=0);
    bool Connect();
    bool IsOpen();
    void Disconnect();

    QString GetHostName() const{return m_hostname;}
    void SetHostName(const QString& value);
    quint16 GetPort() const{return m_port;}
    void SetPort(const quint16 value);
    void SetLongWaitMS(int value){m_longWaitMS = value;}
    void SetShortWaitMS(int value){m_shortWaitMS = value;}
    QString ReadData() const;
    void WriteData(const QString& data) const;
    ~IntSocket();
signals:
    void NotifyConnected();
    void NotifyDisconnected();

private slots:
    void onConnected();
    void onDisConnected();

private:
    QTcpSocket& m_socket;
    QString m_hostname;
    quint16 m_port;
    int m_shortWaitMS;
    int m_longWaitMS;
    explicit IntSocket(const IntSocket& rhs) = delete;
    IntSocket& operator= (const IntSocket& rhs) = delete;
};



