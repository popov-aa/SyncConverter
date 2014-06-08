#ifndef FORMATCONTAINER_H
#define FORMATCONTAINER_H

class QSettings;

#include <QObject>
#include <QHash>

class FormatContainer : public QObject
{

    Q_OBJECT

public:

    FormatContainer(QSettings * settings, QObject * parent = 0);

    QStringList names() const;
    QString format(const QString & name);

public slots:

    void insertFormat(const QString & name, const QString & format);
    void removeFormat(const QString & name);

private:

    void load();
    void save();

private:

    QSettings * m_settings;

    QString m_settingsKey;

    QHash<QString,QString> m_formats;

};

#endif // FORMATCONTAINER_H
