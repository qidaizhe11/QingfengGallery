#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include "DropArea.h"
#include "MyGallery.h"
#include "ThumbnailBarItem.h"
#include "Settings.h"

//int main(int argc, char *argv[])
//{
//    QGuiApplication app(argc, argv);

//    QtQuick2ApplicationViewer viewer;
//    viewer.setMainQmlFile(QStringLiteral("qml/MyGallery/main.qml"));
//    viewer.showExpanded();

//    return app.exec();
//}

int main(int argc, char *argv[])
{
  qDebug() << "In the name of God\n"
              "MyGallery\n"
              "Version 1.0\n"
              "Under GPL V3\n"
              "Author: Daizhe\n"
              "Email: qidaizhe11@gmail.com\n";

  QDir cnf_dir("/mnt/sdcard/mygallery");
  if (!cnf_dir.exists()) {
    cnf_dir.mkpath("/mnt/sdcard/mygallery");
  }

  QApplication app(argc, argv);
  app.setApplicationName("MyGallery");

  QStringList args = app.arguments();
  if (args.count() == 1) {
    args << "/mnt/sdcard/image/";
  }

  for (int i = 1; i < args.count(); ++i) {
    QString argument_str = args.at(1);
    if (!QFileInfo(argument_str).isRelative()) {
      continue;
    }

    argument_str = QDir::currentPath() + "/" + argument_str;
    args.replace(i, argument_str);
  }

  MyGallery* window = new MyGallery();

  if (args.count() == 2) {
    QString argument_str = args.at(1);
    QString dir_str = argument_str;
    QFileInfo file(argument_str);
    if (!file.isDir()) {
      dir_str = file.dir().path();
    }

    window->autoAdd(dir_str,
                    (argument_str == dir_str) ? QString() : argument_str);
  } else {
    for (int i = 1; i < args.count(); ++i) {
      window->autoAdd(args.at(i));
    }
  }

  QObject::connect(&app, SIGNAL(messageReceived(QString)),
                   window, SLOT(add(QString)));

  window->setWindowIcon(":/pics.icon.png");
  window->showFullScreen();

  return app.exec();
}
