import QtQuick 2.0

Rectangle {
    id: thumbnailbar
    color: "#00000000"

    property real cheight: 63

    property int count: 0
    property real item_padding: 5

    property real item_height: (linear) ? item_sml : item_big
    property real item_width: (linear) ? item_sml : item_big

    property real item_big: main.preview_size
    property real item_sml: main.small_preview_size

    property int index_padding: 0

    property real preview_width: (fullscreen) ? 40 + width :
                            width + anchors.leftMargin + anchors.rightMargin
    property real preview_height: (fullscreen) ? 40 + height :
                            height + anchors.leftMargin + anchors.rightMargin
    property real preview_x: (fullscreen) ? -20 : -anchors.leftMargin
    property real preview_y: (fullscreen) ? -20 : -anchors.leftMargin

    property bool fancy: false
    property bool fullscreen: false
    property bool animations_on: true
    property bool smooth_blocker: false

    property int on_preview: -1
    property int last_previewed: -1

    property bool linear: (on_preview != -1)
    property real list_width: (linear && virtual_width > width) ?
                                  virtual_width : width
    property real list_height: (linear || virtual_height < height) ?
                                   height : virtual_height
    property real list_x: 0
    property real lsit_y: 0

    property real virtual_height:
        (item_height + item_padding) *
        Math.floor( (count + index_padding + item_padding - 1)/items_per_line) +
        (item_height + item_padding)
    property real virtual_width: (item_width + item_padding) * count

    property int items_per_line: Math.floor(thumbnailbar.list_width /
                    thumbnailbar.item_width + thumbnailbar.item_padding)
    property int rows_number: Math.floor(count / items_per_line) + 1
    property int last_line_items: count - items_per_line * (rows_number - 1)

    property int highlighted_row: -1
    property int highlighted_column: -1
    property int highlighted_index:
        (highlighted_row > -1 && highlighted_column > -1) ?
            highlighted_row * items_per_line + highlighted_column : -1

    signal preview(int index)
    signal openDir(string path)
    signal rotateLeft_signal()
    signal rotateRight_signal()
    signal loadMore(int index)

    function rotateLeft() {
        if (on_preview === -1)
            return

        rotateLeft_signal()
    }

    function rotateRight() {
        if (on_preview === -1)
            return

        rotateRight_signal()
    }

    onOn_previewChanged: {
//        if (on_preview === -1) {
//            if (windowedMode)
//        }

        startSmoothBlocker()
    }

    Timer {
        id: anim_disabler_timer
        interval: 573
        running: false
        repeat: false
        onTriggered: animations_on = !fullscreen
    }

    Timer {
        id: smooth_blocker_timer
        interval: 837
        running: false
        repeat: false
        onTriggered: smooth_blocker = false
    }

    function startSmoothBlocker() {
        smooth_blocker = true
        smooth_blocker_timer.stop()
        smooth_blocker_timer.start()
    }

    function load(index) {
        loadMore(index)
    }

    function add() {
        var component = Qt.createComponent("ThumbnailBarItem.qml")
        var item = component.createObject(thumbnailbar);
        return item
    }

    function next() {
        thumbnailbar.last_previewed = thumbnailbar.on_preview
        thumbnailbar.on_preview++
        if (thumbnailbar.on_preview == thumbnailbar.count)
            thumbnailbar.on_preview = -1

        thumbnailbar.fancy = false
        thumbnailbar.preview(thumbnailbar.on_preview)
        thumbnailbar.fancy = true
    }

    function previous() {
        if (thumbnailbar.on_preview == -1)
            return

        thumbnailbar.last_previewed = thumbnailbar.on_preview
        thumbnailbar.fancy = false
        thumbnailbar.on_preview--
        thumbnailbar.preview(thumbnailbar.on_preview)
        thumbnailbar.fancy = true
    }

    function unshow() {
        thumbnailbar.last_previewed = thumbnailbar.on_preview
        show(-1)
    }

    function show(index) {
        thumbnailbar.last_previewed = thumbnailbar.on_preview
        thumbnailbar.fancy = false
        thumbnailbar.on_preview = index
        thumbnailbar.preview(index)
        thumbnailbar.fancy = true
    }

    ImageButton {
        id: rotate_left
        source: "image://pixmaps/rotate-left"
        width: 18
        height: 18
        anchors.top: thumbnailbar.top
        anchors.left: thumbnailbar.left
        anchors.topMargin: 10
        anchors.leftMargin: 50
        smooth: true
        z: 101
        visible: (on_preview != -1 && !android)

        onClicked: rotateLeft()
//        onExited: to
//        onEntered: {
    }

    ImageButton {
        id: rotate_right
        source: "image://pixmaps/rotate-right"
        width: 18
        height: 18
        anchors.top: thumbnailbar.top
        anchors.left: thumbnailbar.left
        anchors.topMargin: 10
        anchors.leftMargin: 78
        smooth: true
        z: 101
        visible: (on_preview != -1 && !android)

        onClicked: rotateRight()
    }
}
