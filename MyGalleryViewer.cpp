//-------------------------------------------------------------------------

#include "MyGalleryViewer.h"

#include <QList>
#include <QVariant>
#include <QMetaObject>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>
#include <QGraphicsObject>
#include <QCloseEvent>
#include <QWheelEvent>
#include <QUrl>
#include <QSet>
#include <QSetIterator>
#include <QDir>
#include <QKeySequence>
#include <QDebug>
#include <QApplication>
#include <QMimeData>

#include "ImageProvider.h"
#include "ThumbnailBarItem.h"
#include "MyGalleryColors.h"
#include "DropArea.h"
#include "Settings.h"
#include "MyGallery_global.h"
#include "silicon/sstring.h"
#include "silicon/sstringlist.h"
#include "MyGallery.h"

#define LOAD_STEP_SIZE 100

//-------------------------------------------------------------------------

class MyGalleryViewerPrivate
{
public:
  QList<ThumbnailBarItem*> list;
  QString id;

  QDeclarativeEngine* engine;
  QDeclarativeContext* root;

  QObject* thumnailbar;

  Settings* settings;

  bool on_process;
  int prev_index;

  QSet<ThumbnailBarItem*> loaded_lights;
};

//-------------------------------------------------------------------------
// public

MyGalleryViewer::MyGalleryViewer(QWidget *parent) :
  QDeclarativeView(parent)
{
  QString thumbnails_path = THUMBNAILS_PATH;
  if (!QDir(thumbnails_path).exists()) {
    QDir().mkpath(thumbnails_path);
  }
  const QStringList& thumbnails = QDir(thumbnails_path).entryList(QDir::Files,
                                                                  QDir::Time);
  for (int i = 100000; i < thumbnails.count(); ++i) {
    QFile::remove(thumbnails_path + "/" + thumbnails.at(i));
  }

  p = new MyGalleryViewerPrivate;
  p->id = ImageProvider::getId();
  p->on_process = false;
  p->prev_index = -1;

  p->settings = new Settings(this);

#ifdef Q_OS_LINUX
  ImageProvider::addPixmap("folder",
        QIcon::fromTheme("folder").pixmap(128, 128));
  ImageProvider::addPixmap("rotate-left",
        QIcon(":/mygallery/pics/object-rotate-left.png").pixmap(32, 32));
  ImageProvider::addPixmap("rotate-right",
        QIcon(":/mygallery/pics/object-rotate-right.png").pixmap(32, 32));
#else
  ImageProvider::addPixmap("folder",
        QIcon(":/mygallery/pics/folder.png").pixmap(128, 128));
  ImageProvider::addPixmap("rotate-left",
        QIcon(":/mygallery/pics/object-rotate-left.png").pixmap(32, 32));
  ImageProvider::addPixmap("rotate-right",
        QIcon(":/mygallery/pics/object-rotate-right.png").pixmap(32, 32));
#endif

  p->engine = engine();
  p->engine->addImageProvider(QLatin1String("pixmaps"), new ImageProvider());

  p->root = rootContext();
  p->root->setContextProperty("Colors", new MyGalleryColors(this));
  p->root->setContextProperty("View", this);
  p->root->setContextProperty("MyGallery", MyGallery::instance());
  p->root->setContextProperty("Settings", p->settings);

  qmlRegisterType<DropArea>("com.mygallery.droparea", 1, 0, "DropArea");
  setSource(QUrl("qrc:/mygallery/qml/MyGallery/main.qml"));
//    viewer.setMainQmlFile(QStringLiteral("qml/MyGallery/main.qml"));


  p->thumnailbar = rootObject()->findChild<QObject*>("thumbnailbar");

#ifdef Q_OS_LINUX
  rootObject()->setProperty("linux", true);
  rootObject()->setProperty("os", "linux");
#endif
#ifdef Q_OS_MAC
  rootObject()->setProperty("mac", true);
  rootObject()->setProperty("os", "mac");
#endif
#ifdef Q_OS_WIN32
  rootObject()->setProperty("windows", true);
  rootObject()->setProperty("os", "windows");
#endif
#ifdef Q_OS_ANDROID
  rootObject()->setProperty("android", true);
  rootObject()->setProperty("os", "android");
#endif

  setResizeMode(QDeclarativeView::SizeRootObjectToView);
  setAcceptDrops(true);

  //TODO:
//  connect(p->thumnailbar, SIGNAL())
}

ThumbnailBarItem* MyGalleryViewer::add(const QString &path, const QString &name)
{
  return insert(count(), path, name);
}

//ThumbnailBarItem* MyGalleryViewer::insert(int index, const QString &path,
//                                          const QString &name)
//{
//  QFileInfo file(path);
//  ThumbnailBarItem* item = insert(index, name);

//  if (!file.isDir()) {
//    if (!item->setPixmap(path)) {
//      delete item;
//      item = 0;
//    }
//  } else {
//    item->setDirectoryPath(path);
//  }

//  return item;
//}

//ThumbnailBarItem* MyGalleryViewer::insert(const QString &path,
//                                          const QString &name)
//{

//}

//-------------------------------------------------------------------------
// public slots

void MyGalleryViewer::autoAdd(const QStringList &list)
{
  for (int i = 0; i < list.count(); ++i) {
    autoAdd(list.at(i));
  }
}

void MyGalleryViewer::autoAdd(const QString &path, const QString &show)
{
  QString absolute_path = QDir(path).absolutePath();
  QString absolute_show = (show.isEmpty() ? QString() :
                                            QDir(show).absolutePath());

  QFileInfo file(absolute_path);
  int start = count();

  if (!show.isEmpty()) {
    QFileInfo shf(absolute_show);
    insert(start, absolute_show, shf.fileName());

    QMetaObject::invokeMethod(p->thumbnailbar, "show", Q_ARG(QVariant, start));
  }
  if (!file.isDir()) {
    add(absolute_path, file.fileName());
  } else {
    SStringList folders = QDir(absolute_path).entryList(
          QDir::NoDotAndDotDot | QDir::Dirs, QDir::Name);
    SStringList files = QDir(absolute_path).entryList(
          QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    SStringList list;

    qSort(files.begin(), files.end());
    qSort(folders.begin(), folders.end());

    list << ".." << folders << files;

    p->on_process = true;
    for (int i = 0; i < list.count(); ++i) {
      if (i % 20 == 0) {
        QApplication::processEvents();
      }

      QString ip = absolute_path + "/" + list.at(i);
      if (ip == absolute_show) {
        continue;
      }

      insert(start + i, ip, list.at(i));
    }

    p->on_process = false;
  }

  if (!show.isEmpty()) {
    for (int i = 0;
         i < count() && p->thumbnailbar->property("on_preview").toInt() == -1;
         ++i) {
      ThumbnailBarItem* item = at(i);
      if (item->pixmap() == absolute_show) {
        QMetaObject::invokeMethod(p->thumbnailbar, "show", Q_ARG(QVariant, i));
      }
    }
  }
}
