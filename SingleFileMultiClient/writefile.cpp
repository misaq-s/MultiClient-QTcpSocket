#include "writefile.h"
#include <QDebug>
///
/// \brief WriteFile::WriteFile
/// \param fileName
/// Set file Object
///
WriteFile::WriteFile(QFile *file)
{
    m_file = file;
}
///
/// \brief WriteFile::WriteFile
/// \param fileName
/// Set file name
///
WriteFile::WriteFile(QString fileName)
{
    m_file = new QFile(fileName);
}
///
/// \brief WriteFile::write
/// \param data
/// Open and write on file
///
void WriteFile::write(QByteArray data)
{
    m_data = data;
    // Try to open file
    if(!m_file->isOpen())
        if(!m_file->open(QFile::Append | QFile::Text))
        {
            return;
        }
    // Write data on file
    QTextStream out(m_file);
    out << data;
}
///
/// \brief WriteFile::close
/// Close file m_file object
///
void WriteFile::close()
{
    if(m_file->isOpen())
    {
        m_file->close();
    }
}
