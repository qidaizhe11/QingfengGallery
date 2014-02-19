#include "MyGallery.h"

#include <QToolBar>
#include <QGraphicsObject>
#include <QResizeEvent>
#include <QDebug>
#include <QAction>

#include "MyGalleryViewer.h"
#include "Settings.h"

MyGallery* mygallery = 0;

class MyGalleryPrivate
{
public:
  MyGalleryViewer* viewer;
  QToolBar* toolbar;
  bool fullscreen_mode;
  bool windowed_mode;
  QSize size_tmp;
  QPoint pos_tmp;
};

MyGallery::MyGallery(QWidget* parent)
  : QMainWindow(parent)
{
  mygallery = this;
  p = new MyGalleryPrivate;
  p->fullscreen_mode = false;
  p->viewer = new MyGalleryViewer(this);
  p->toolbar = new QToolBar();
  p->toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  p->toolbar->setAllowedAreas(Qt::TopToolBarArea);
  p->toolbar->setMovable(false);

//#ifndef Q_OS_ANDROID
//  if ()

  setCentralWidget(p->viewer);
  addToolBar(Qt::TopToolBarArea, p->toolbar);
  setWindowTitle("Qingfeng Gallery");
  setupActions();
}

MyGallery::~MyGallery()
{
  delete p;
}

void MyGallery::setupActions()
{
  p->toolbar->addAction(QIcon::fromTheme("object-rotate-left"),
                  tr("Rotate Left"), p->viewer->obj(), SLOT(rotateLeft()));
  p->toolbar->addAction(QIcon::fromTheme("object-rotate-right"),
                  tr("Rotete Right"), p->viewer->obj(), SLOT(rotateRight()));
}

Settings* MyGallery::settings() const
{
  return p->viewer->settings();
}

MyGallery* MyGallery::instance()
{
  return mygallery;
}

void MyGallery::autoAdd(const QStringList &list)
{
  p->viewer->autoAdd(list);
}

void MyGallery::autoAdd(const QString &path, const QString &show)
{
  p->viewer->autoAdd(path, show);
}

void MyGallery::resizeEvent(QResizeEvent *e)
{
  p->viewer->settings()->setValue("general/size", e->size());
  p->size_tmp = e->size();

  QMainWindow::resizeEvent(e);
}

void MyGallery::moveEvent(QMoveEvent *e)
{
  p->pos_tmp = e->pos();

  QMainWindow::moveEvent(e);
}
