#ifndef MYGALLERYCOLORS_H
#define MYGALLERYCOLORS_H

#include <QObject>
#include <QColor>

class MyGalleryColorsPrivate;

class MyGalleryColors : public QObject
{
  Q_OBJECT
public:
  explicit MyGalleryColors(QObject *parent = 0);
  ~MyGalleryColors();

  Q_INVOKABLE QColor window() const;
  Q_INVOKABLE QColor windowText() const;
  Q_INVOKABLE QColor base() const;

private:
  MyGalleryColorsPrivate* p;
};

#endif // MYGALLERYCOLORS_H
