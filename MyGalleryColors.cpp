#include "MyGalleryColors.h"

#include <QPalette>

class MyGalleryColorsPrivate
{
public:
  QPalette palette;
};

MyGalleryColors::MyGalleryColors(QObject *parent) :
  QObject(parent)
{
  p = new MyGalleryColorsPrivate;
}

QColor MyGalleryColors::window() const
{
  return p->palette.window().color();
}

QColor MyGalleryColors::windowText() const
{
  return p->palette.windowText().color();
}

QColor MyGalleryColors::base() const
{
  return p->palette.base().color();
}
