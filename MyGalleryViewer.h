#ifndef MYGALLERYVIEWER_H
#define MYGALLERYVIEWER_H

#include <QtDeclarative/QDeclarativeView>
#include <QPixmap>
#include <QVariant>

class Settings;
class ThumbnailBarItem;
class MyGalleryViewerPrivate;

class MyGalleryViewer : public QDeclarativeView
{
  Q_OBJECT
public:
  explicit MyGalleryViewer(QWidget *parent = 0);
  ~MyGalleryViewer();

  ThumbnailBarItem* add(const QString& path, const QString& name);
  ThumbnailBarItem* insert(int index, const QString& path,
                           const QString& name);
  ThumbnailBarItem* insert(const QString& path, const QString& name);

  void remove(ThumbnailBarItem* item);
  void remove(int index);

  ThumbnailBarItem* at(int index) const;
  int indexOf(ThumbnailBarItem* item) const;
  Q_INVOKABLE QObject* objectAt(int index);

  int count() const;
  bool isEmpty() const;

  int currentIndex() const;
  QObject* obj() const;

  void setBackgroundOpacity(qreal opacity);
  qreal backgroundOpacity() const;

  void setCloseOnClick(bool stt);
  bool closeOnClick() const;

  void setFullscreen(bool stt);
  bool fullscreen() const;

  Q_INVOKABLE bool onProcess() const;

  Settings* settings() const;

public slots:
  void autoAdd(const QStringList& list);
  void autoAdd(const QString& path, const QString& show = QString());

  void clear();
  void undoCurrent();

  void loadMore(int index);

signals:
  void wheel(qreal delta);

private slots:
  void openDir(const QString& path);
  void itemDestroyed(QObject* obj);
  void reindex();
  void currentIndexChanged(int index);
  void itemAddRequest(const QString& path);

protected:
  void wheelEvent(QWheelEvent* event);
  void dropEvent(QDropEvent* event);
  void dragEnterEvent(QDragEnterEvent* event);
  void closeEvent(QCloseEvent* event);
  void resizeEvent(QResizeEvent* event);

private:
  MyGalleryViewerPrivate* p;
};

#endif // MYGALLERYVIEWER_H
