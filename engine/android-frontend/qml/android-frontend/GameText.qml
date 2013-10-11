import QtQuick 2.0
import "utils.js" as U

Text{
    font.pixelSize: 18
    MouseArea {
        anchors.fill: parent
        onClicked: {
            U.click(mouse.x, mouse.y)
        }
    }
}
