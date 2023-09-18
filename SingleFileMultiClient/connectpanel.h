#ifndef CONNECTPANEL_H
#define CONNECTPANEL_H

#include <QWidget>
#include <tcpclient.h>
#include <writefile.h>
#include <QMutex>
#include <QHostAddress>
#include <QFile>
namespace Ui {
class ConnectPanel;
}
class ConnectPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectPanel(QWidget *parent = nullptr);
    ~ConnectPanel();
    void setMutex(QMutex *mutex);
    void setFile(QFile *file);


private:
    TcpClient *m_tcpClient = nullptr;
    QMutex *m_mutex = nullptr;
    QFile *m_file = nullptr;
    Ui::ConnectPanel *ui;

private slots:
    void on_pbConnect_clicked();
    void m_disConnected();
    void m_connected();
};
#endif // CONNECTPANEL_H
