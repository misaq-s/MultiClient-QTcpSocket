#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <tcpclient.h>
#include <writefile.h>
#include <QFile>
#include <QMutex>
#include <connectpanel.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMutex *m_mutex = nullptr;
    QFile *m_file = nullptr;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
