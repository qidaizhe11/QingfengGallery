#ifndef MYGALLERY_GLOBAL_H
#define MYGALLERY_GLOBAL_H

#include <QDir>

#ifndef Q_OS_ANDROID
#define THUMBNAILS_PATH QDir::homePath() + "/.thumbnails/normal"
#else
#define THUMBNAILS_PATH QString("/mnt/sdcard/mygallery/.thumbnails/")
#endif

#endif // MYGALLERY_GLOBAL_H
