#ifndef CONVERTER_H
#define CONVERTER_H

#include <QThread>

class Converter : public QThread
{

    Q_OBJECT

public:

    explicit Converter(QObject * parent = 0);
    virtual ~Converter();

public slots:

    void convertDirectory(const QString & inputDirpath,
                          const QString & outputDirpath,
                          const QString & extension,
                          const QString & format);
    void stop();

    void clear();

signals:

    void fileConvertFailed(QString output);

protected:

    virtual void run() override;
    void progressDirectory(const QString & inputDirpath,
                           const QString & outputDirpath);
    void convert(const QString & inputFilepath,
                 const QString & outputFilepath);

private:

    QString m_inputDirpath;
    QString m_outputDirpath;
    QString m_extension;
    QString m_format;

    QString m_currentFilepath;

};

#endif // CONVERTER_H
