#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tcpclient.h>
#include <QHostAddress>
#include <QByteArray>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_mutex = new QMutex;
    m_file = new QFile("DataFromClients.txt");
    ui->setupUi(this);
    // set panels mutex and file object
    ui->wdPanel1->setMutex(m_mutex);
    ui->wdPanel1->setFile(m_file);
    //
    ui->wdPanel2->setMutex(m_mutex);
    ui->wdPanel2->setFile(m_file);
    //
    ui->wdPanel3->setMutex(m_mutex);
    ui->wdPanel3->setFile(m_file);
    //
    ui->wdPanel4->setMutex(m_mutex);
    ui->wdPanel4->setFile(m_file);
    //
    ui->wdPanel5->setMutex(m_mutex);
    ui->wdPanel5->setFile(m_file);
}
MainWindow::~MainWindow()
{
    delete ui;
}
