#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QMainWindow>
#include <QtCore>
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <writefile.h>
#include <QFile>
#include <QWidget>
class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QString ip , uint port , QFile *file , QMutex *mutex);
    explicit TcpClient();
    void setIp(QString ip);
    void setPort(uint port);
    void setFile(QFile *file);
    void setMutex(QMutex *mutex);
    void runThread();

private:
    QString m_Ip = "";
    uint m_Port = 0;
    QByteArray m_data = "";
    QTcpSocket *m_socket = nullptr;
    WriteFile *m_writeFile = nullptr;
    QThread *m_thread= nullptr;
    QMutex *m_mutex = nullptr;
    QString m_fileName = "";

private slots :
    void m_doConnect();
    void m_readyRead();
    void m_disConnect();

signals:
    void disConnected();
    void connected();
    void refused();
    void readData(QByteArray);
};
#endif // TCPCLIENT_H
