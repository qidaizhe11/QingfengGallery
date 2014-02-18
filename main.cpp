#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

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
}
