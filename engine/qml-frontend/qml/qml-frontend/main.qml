import QtQuick 2.0
import rooms 1.0

Rectangle {
    id: window
    width: 800
    height: 600

    GameView {
        id: game
        anchors.fill: window
        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                game.click(mouse.x, mouse.y);
            }
            onPositionChanged: {
                game.mouseMove(mouse.x, mouse.y);
            }
        }
        // Updates the game at 60 fps
        NumberAnimation on t {
            loops: Animation.Infinite
            from: 0
            to: 60
            duration: 1000
        }
    }
}
