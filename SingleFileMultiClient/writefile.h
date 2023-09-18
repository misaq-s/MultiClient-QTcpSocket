#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtCore>
class WriteFile : public QObject
{
public:
    WriteFile(QFile *file);
    WriteFile(QString fileName);
    void write(QByteArray data);
    void close();

private:
    QString m_fileName = "";
    QByteArray m_data = NULL;
    QFile *m_file = nullptr;
};
#endif // WRITEFILE_H
