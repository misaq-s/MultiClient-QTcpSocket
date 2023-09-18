#include "tcpclient.h"
#include <writefile.h>
///
/// \brief TcpClient::TcpClient
/// Make new thread object
///
TcpClient::TcpClient()
{
    m_thread = new QThread();
}
///
/// \brief TcpClient::TcpClient
/// \param ip
/// \param port
/// \param file
/// \param mutex
/// override to set all attributes
///
TcpClient::TcpClient(QString ip, uint port, QFile *file, QMutex *mutex)
{
    this->m_Ip=ip;
    this->m_Port=port;
    m_mutex = mutex;
    m_writeFile = new WriteFile(file);
    m_thread = new QThread();
}
///
/// \brief TcpClient::setIp
/// \param ip
/// Set ip
///
void TcpClient::setIp(QString ip)
{
    m_Ip = ip;
}
///
/// \brief TcpClient::setPort
/// \param port
/// Set port
///
void TcpClient::setPort(uint port)
{
    m_Port = port;
}
///
/// \brief TcpClient::setFile
/// \param file
/// Make Object of WriteFile() and point to file object in mainwindow
///
void TcpClient::setFile(QFile *file)
{
    m_writeFile = new WriteFile(file);
}
///
/// \brief TcpClient::setMutex
/// \param mutex
/// Set m_mutex to point mutex object in mainwindow
///
void TcpClient::setMutex(QMutex *mutex)
{
    m_mutex = mutex;
}
///
/// \brief TcpClient::runThread
/// Move this to thread and start
///
void TcpClient::runThread()
{
    //  Move class to thread and connect thread start to m_doConnect() slot
    this->moveToThread(m_thread);
    connect(m_thread,SIGNAL(started()),this,SLOT(m_doConnect()));
    m_thread->start();
}
///
/// \brief TcpClient::m_doConnect
/// Make new QTcpSocket and try to connect
///
void TcpClient::m_doConnect()
{
    m_socket = new QTcpSocket;
    // Connect to QTcpSocket signals
    QObject::connect(m_socket, SIGNAL(readyRead()),this, SLOT(m_readyRead()));
    QObject::connect(m_socket, SIGNAL(disconnected()),this,SLOT(m_disConnect()));
    QObject::connect(m_socket, &QTcpSocket::connected,this,&TcpClient::connected);
    // Make connection to host
    m_socket->connectToHost(m_Ip,m_Port);
    // Wait to connecting for 5s
    if(!m_socket->waitForConnected(5000))
    {
        // emit refused signal
        emit refused();
    }
}
///
/// \brief TcpClient::m_readyRead
/// Read and send data to write file
///
void TcpClient::m_readyRead()
{

    m_data = m_socket->readAll();
    //  lock the mutex
    m_mutex->lock();
    m_writeFile->write(m_data);
    //  unlock the mutex
    m_mutex->unlock();
}
///
/// \brief TcpClient::m_disConnect
/// Close file & delete objects
/// Quit of thread
/// emit disconnect signal
///
void TcpClient::m_disConnect()
{
    // Close file and delete object
    if(m_writeFile != nullptr){
        m_writeFile->close();
        m_writeFile->deleteLater();
    }
    m_socket->deleteLater();
    emit disConnected();
    m_thread->quit();
}
