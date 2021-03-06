#include "Settings.h"

Settings::Settings(QObject* parent)
  : QSettings("/mnt/sdcard/mygallery/config", QSettings::IniFormat, parent)
{
}

void Settings::setValue(const QString &key, const QVariant &value)
{
  QSettings::setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const
{
  return QSettings::value(key, defaultValue);
}

void Settings::remove(const QString& key)
{
  QSettings::remove(key);
}
