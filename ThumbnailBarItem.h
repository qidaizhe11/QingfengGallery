#ifndef THUMBNAILBARITEM_H
#define THUMBNAILBARITEM_H

#include <QObject>
#include <QPixmap>

class ThumbnailBarItemPrivate;

class ThumbnailBarItem : public QObject
{
  Q_OBJECT

  friend class MyGalleryViewer;
public:
  ThumbnailBarItem(QObject* item);
  ~ThumbnailBarItem();

private:
  ThumbnailBarItemPrivate* p;
};

#endif // THUMBNAILBARITEM_H
