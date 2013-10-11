import QtQuick 2.0
import "utils.js" as U

Image {
    cache: true
    property int cursorShape: Qt.ArrowCursor
    MouseArea {
        id: mouse
        cursorShape: parent.cursorShape
        anchors.fill: parent
        onClicked: {
            U.click(mouse.x, mouse.y)
        }
    }
}
