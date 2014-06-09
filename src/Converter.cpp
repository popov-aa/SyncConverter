#include "Converter.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QProcess>

Converter::Converter(QObject * parent) :
    QThread(parent)
{
}

Converter::~Converter()
{
    clear();
}

void Converter::convertDirectory(const QString & inputDirpath,
                                 const QString & outputDirpath,
                                 const QString & extension,
                                 const QString & format)
{
    m_inputDirpath = inputDirpath;
    m_outputDirpath = outputDirpath;
    m_extension = extension;
    m_format = format;

    start();
}

void Converter::stop()
{
    exit();
    clear();
}

void Converter::clear()
{
    if (!m_currentFilepath.isEmpty())
    {
        QFile::remove(m_currentFilepath);
    }
}

void Converter::run()
{
    progressDirectory(m_inputDirpath, m_outputDirpath);
}

void Converter::progressDirectory(const QString & inputDirpath,
                                  const QString & outputDirpath)
{
    QDir inputDir(inputDirpath);
    QDir outputDir(outputDirpath);

    foreach (QFileInfo fi, inputDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable, QDir::Name))
    {
        QString outputFilepath = QString("%1/%2.%3").arg(outputDirpath).arg(fi.fileName().section('.', 0, -2)).arg(m_extension);
        if (!QFile::exists(outputFilepath))
        {
            convert(fi.absoluteFilePath(), outputFilepath);
        }
    }

    foreach (QFileInfo di, inputDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable, QDir::Name))
    {
        if (!outputDir.exists(di.fileName()))
        {
            outputDir.mkdir(di.fileName());
        }
        progressDirectory(di.absoluteFilePath(), QString("%1/%2").arg(outputDirpath).arg(di.fileName()));
    }
}

void Converter::convert(const QString & inputFilepath, const QString & outputFilepath)
{
    QString program = m_format;
    program.replace("%input_filepath", inputFilepath);
    program.replace("%output_filepath", outputFilepath);

    m_currentFilepath = outputFilepath;

    QProcess process;
    process.start(program);
    process.waitForFinished(600000);

    m_currentFilepath.clear();

    if (!process.exitCode())
    {
        emit fileConvertFailed(QString(process.readAllStandardError()));
    }
}
