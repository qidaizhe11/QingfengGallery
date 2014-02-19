import QtQuick 2.0

Image {
    id: image_button
    width: 100
    height: 62

    signal clicked()
    signal entered()
    signal exited()

    property bool auto_hide: false
    onAuto_hideChanged: if (auto_hide) opacity = 0.001

    Behavior on opacity {
        NumberAnimation {
            easing.type: Easing.Linear;
            duration: (disable_animations) ? 537 : 0
        }
    }

    function show() {
        image_button.opacity = 1
        if (auto_hide)
            timer.running = false
    }

    function hide() {
        if (auto_hide)
            timer.running = true
    }

    Timer {
        id: timer
        interval: 1000
        repeat: false
        running: false
        onTriggered: image_button.opacity = 0.001
    }

    MouseArea {
        id: mouse_area
        hoverEnabled: true
        anchors.fill: parent
        onEntered: {
            image_button.width += 2
            image_button.height += 2
            image_button.enabled()
            show()
        }
        onExited: {
            image_button.width -= 2
            image_button.height -= 2
            image_button.exited()
            hide()
        }
        onClicked: image_button.clicked()
    }
}
