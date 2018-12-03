#include "intsocket.h"
#include <QTcpSocket>
#include <QDebug>
#include "utils.h"
#include <QString>
IntSocket::IntSocket(QObject *parent) :
    QObject(parent),
    m_socket(*new QTcpSocket(this)),
    m_hostname(""),
    m_port(0),
    m_shortWaitMS(0),
    m_longWaitMS(0)
{
    //wiring up our slots to connect method,in order to know when it is connected and
    //to be implemented int the notify function
    connect(&m_socket, &QTcpSocket::connected,this,&IntSocket::onConnected);
    connect(&m_socket, &QTcpSocket::disconnected,this,&IntSocket::onDisConnected);
}

IntSocket::~IntSocket()
{
    Utils::DestructorMsg(this);
}

void IntSocket::SetHostName(const QString &value)
{
    m_hostname = value;
}

void IntSocket::SetPort(quint16 value)
{
    m_port = value;
}

bool IntSocket::Connect()
{
    qDebug() << "Attempting to connect to " << m_hostname << "On Port" << m_port <<
                "with the wait time of" << m_longWaitMS;

    m_socket.connectToHost(m_hostname,m_port,QTcpSocket::ReadWrite);
    return m_socket.waitForConnected(m_longWaitMS);
}

bool IntSocket::IsOpen()
{

    return m_socket.isOpen();
}

void IntSocket::Disconnect()
{
    if(!IsOpen()) return;
    m_socket.disconnectFromHost();
}
void IntSocket::onConnected()
{
    emit NotifyConnected();
}
void IntSocket::onDisConnected()
{
    emit NotifyDisconnected();
}
//providing reading and writing to the socket after setting up
void IntSocket::WriteData(const QString &data) const
{
    int bytes_written = m_socket.write(qPrintable(data));
    qDebug() <<"Number of bytes written. "<<bytes_written;
}
QString IntSocket::ReadData() const
{
    if(!m_socket.isReadable())
    {
        return "Socket is not readable";
    }
    QString result;
    //since we can't expect the socket to read all the data at once
    //we need to loop over till all the data has been read
    while(!m_socket.atEnd())
    {
        result.append(m_socket.readAll());
        m_socket.waitForReadyRead(m_shortWaitMS);
    }
    return result;
}
