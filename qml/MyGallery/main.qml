import QtQuick 2.0
import com.mygallery.droparea 1.0

Rectangle {
    id: main
//    color: (android || on_window)

    property real back_opacity
//    property alias linear:

    property real preview_size: Settings.value("general/preview_size", 50) *
                                ((android) ? 192 : 160) / 50
    property real small_preview_size:
        Settings.value("general/small_preview_size", 50) * 92 / 50
}
