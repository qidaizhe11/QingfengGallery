#ifndef MYGALLERY_H
#define MYGALLERY_H

#include <QMainWindow>

class Settings;
class MyGalleryPrivate;

class MyGallery : public QMainWindow
{
  Q_OBJECT

public:
  MyGallery(QWidget* parent = 0);
  ~MyGallery();

  void setFullscreen(bool stt);
  bool fullscreen() const;

  Settings* settings() const;

  Q_INVOKABLE static MyGallery* instance();

public slots:
  void autoAdd(const QStringList& list);
  void autoAdd(const QString& path, const QString& show = QString());

  void toggleFullScreen();
  void setFullscreenWindow();
  void setNormalWindow();

protected:
  void resizeEvent(QResizeEvent *e);
  void moveEvent(QMoveEvent* e);

private:
  void setupActions();

private:
  MyGalleryPrivate* p;
};

#endif // MYGALLERY_H
