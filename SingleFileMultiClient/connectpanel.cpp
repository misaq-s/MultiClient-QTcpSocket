#include "connectpanel.h"
#include "ui_connectpanel.h"
#include <tcpclient.h>
ConnectPanel::ConnectPanel( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectPanel)
{
    ui->setupUi(this);
    m_tcpClient = new TcpClient;
}
ConnectPanel::~ConnectPanel()
{
    delete ui;
}
///
/// \brief ConnectPanel::setMutex
/// \param mutex
///  Set m_mutex to point mutex object in mainwindow
///
void ConnectPanel::setMutex(QMutex *mutex)
{
    m_mutex = mutex;
}
///
/// \brief ConnectPanel::setFile
/// \param file
/// Set m_file to point file object in mainwindow
///
void ConnectPanel::setFile(QFile *file)
{
    m_file = file;
}
///
/// \brief ConnectPanel::on_pbConnect_clicked
/// Check Ip & Port if valid make object of TcpClient to connect
///
void ConnectPanel::on_pbConnect_clicked()
{
    bool validIp = false;
    bool validPort = true;
    QString Ip = "";
    uint Port  = 0;
    // Check valid ip
    QHostAddress address;
    Ip = ui->leIp->text();
    if (address.setAddress(Ip))
    {
        validIp = true;
    }
    //  Valid range of port is limit on SpinBox in ui
    Port = ui->sbPort->value();
    // Make object to connection & connect to signals
    if(validIp && validPort)
    {
        ui->lbShowStatus->setText("ip & port is valid");
        // Make a new object of TcpClient() and call mutex by reference
        m_tcpClient->setIp(Ip);
        m_tcpClient->setPort(Port);
        m_tcpClient->setMutex(m_mutex);
        m_tcpClient->setFile(m_file);
        m_tcpClient->runThread();
        // Connect to TcpClient signals to know status of connection
        QObject::connect(m_tcpClient,SIGNAL(connected()),this,SLOT(m_connected()));
        QObject::connect(m_tcpClient,&TcpClient::refused,[=]{
            ui->lbShowStatus->setText("connection refused");
        });
        QObject::connect(m_tcpClient,SIGNAL(disConnected()),this,SLOT(m_disConnected()));
    }
    // Show status to client
    else if(!validIp && !validPort)
    {
        ui->lbShowStatus->setText("Ip&Port not valid");
    }
    else if (!validIp)
    {
        ui->lbShowStatus->setText("Ip not valid");
    }
}
///
/// \brief ConnectPanel::m_disConnected
/// Set gbCLient disabeld to false & set status to disconnected
///
void ConnectPanel::m_disConnected()
{
    ui->gbClient->setDisabled(false);
    ui->lbShowStatus->setText("disconnected");
}
///
/// \brief ConnectPanel::m_disConnected
/// Set gbCLient disabeld to true & set status to connected
///
void ConnectPanel::m_connected()
{
    ui->gbClient->setDisabled(true);
    ui->lbShowStatus->setText("connected");
}
