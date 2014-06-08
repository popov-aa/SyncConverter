#include "FormatContainer.h"

#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>

FormatContainer::FormatContainer(QSettings * settings, QObject * parent) :
    QObject(parent),
    m_settings(settings)
{
    m_settingsKey = "FORMATS";
    load();
}

QStringList FormatContainer::names() const
{
    return m_formats.keys();
}

QString FormatContainer::format(const QString & name)
{
    return m_formats[name];
}

void FormatContainer::insertFormat(const QString & name, const QString & format)
{
    m_formats[name] = format;
    save();
}

void FormatContainer::removeFormat(const QString & name)
{
    m_formats.remove(name);
    save();
}

void FormatContainer::load()
{
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(m_settings->value(m_settingsKey));
    QJsonObject jsonObject = jsonDocument.object();

    foreach (QString key, jsonObject.keys())
    {
        m_formats[key] = jsonObject.value(key).toString();
    }
}

void FormatContainer::save()
{
    QJsonObject jsonObject;

    foreach (QString key, m_formats.keys())
    {
        jsonObject.insert(key, m_formats[key]);
    }

    QJsonDocument jsonDocument(jsonObject);
    m_settings->setValue(m_settingsKey, jsonDocument.toVariant());
    m_settings->sync();
}
