#include "instrument.h"
#include "intsocket.h"
#include "utils.h"
#include <Qdebug>
#include "provider.h"
#include "settings.h"

Instrument::Instrument(QObject *parent, IntSocket& sock) :
    QObject(parent),
    m_intSocket(sock),
    m_lastCommandSent("")
{
    WireConnections();
}

Instrument::~Instrument()
{
    Utils::DestructorMsg(this);
}

void Instrument::WireConnections()
{
    connect(&m_intSocket,&IntSocket::NotifyConnected,this,&Instrument::onConnected);
    connect(&m_intSocket,&IntSocket::NotifyDisconnected,this,&Instrument::onDisConnected);
}

void Instrument::SetShortWaitMS(int value)
{
   m_intSocket.SetShortWaitMS(value);
}

void Instrument::SetLongWaitMS(int value)
{
    m_intSocket.SetLongWaitMS(value);
}

void Instrument::onHostNameChanged(const QString &hostName)
{
    m_intSocket.SetHostName(hostName);
}
void Instrument::onPortChanged(const quint16 port)
{
    m_intSocket.SetPort(port);
}
void Instrument::Connect()
{
    DisConnect();
    //useful when we are connected to a different hostname and somehow it has changed.
    bool connected = m_intSocket.Connect();

    if(!connected)
    {
       emit NotifyErrorDetected(tr("ERROR: Unable to connect"));
    }
}
//If connection was successful we can make anyone know that we have a connection by wiring socket connection to the OnConnected slot.
void Instrument::onConnected()
{
    emit NotifyConnected();
}

bool Instrument::IsConnected() const
{
    return m_intSocket.IsOpen();
}

void Instrument::DisConnect() const
{
    if(m_intSocket.IsOpen())
    {
        m_intSocket.Disconnect();
    }
    else
    {
        emit NotifyDisConnected();
    }
}

void Instrument::onDisConnected()
{
    emit NotifyDisConnected();
}

QString Instrument::GetHostName() const
{
    return m_intSocket.GetHostName();
}
quint16 Instrument::GetPort() const
{
    return m_intSocket.GetPort();
}
void Instrument::onSendRequest(const QString &dataToSend)
{
    m_lastCommandSent = dataToSend;
    qDebug() << "Intrument Ready to send data :" <<dataToSend;
    m_intSocket.WriteData(dataToSend);
    emit NotifyDataSent(dataToSend);
}
void Instrument::onReceiveRequest()
{
    QString input_buffer = m_intSocket.ReadData();
    if(input_buffer.size()==0)
    {
        emit NotifyDataReceived("No data received");
    }
    else
    {
        emit NotifyDataReceived(input_buffer);
    }
}

void Instrument::onPulseWidthChange(double value)
{
    Settings& settings = Provider::GetSettingsAsSingleton();
    auto pw_cmd = settings.getPwCommand() + "%1;";
    auto full_cmd = pw_cmd.arg(value);
    m_intSocket.WriteData(full_cmd);
    emit NotifyStatusUpdated(full_cmd);
}
