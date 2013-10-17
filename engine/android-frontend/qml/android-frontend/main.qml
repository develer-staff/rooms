import QtQuick 2.0
import rooms 1.0
import "utils.js" as U

Rectangle {
    id: window
    width: 360
    height: 360

    BorderImage {
        id: button
        source: "assets:/ui/simplebutton.png"
        width: quitText.width+8
        height: quitText.height+6
        border{
            top:2
            right:2
            bottom:2
            left:2
        }

        anchors {
            bottom: parent.bottom
            right: parent.right
            bottomMargin: 7
            rightMargin: 7
        }
        Text {
            id: quitText
            font.pointSize: 14
            anchors.centerIn: parent
            text: "Quit"
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                parent.source = "assets:/ui/simplebutton_pressed.png"
            }

            onReleased: {
                parent.source = "assets:/ui/simplebutton.png"
            }

            onClicked: {
                Qt.quit();
            }
        }

        z:100
    }

    onWidthChanged: {
        game.windowWidth = width;
    }

    onHeightChanged: {
        game.windowHeight = height;
    }

    property var images: new Object;
    property var texts: new Object;

    function disposeTexts(){
        var orderedTexts = new Array;
        for (var i in texts){
            var j = 0;
            while(j < orderedTexts.length){
                if (orderedTexts[j].y > texts[i].y)
                    break;
                ++j;
            }
            orderedTexts.splice(j, 0, texts[i]);
        }
        for(var i = 0; i < orderedTexts.length-1; i++){
            for(var j = i+1; j < orderedTexts.length; j++){
                if (orderedTexts[i].opacity !== 0 &&
                        orderedTexts[j].opacity !== 0 &&
                        orderedTexts[j].y < window.height){
                    var diff = (orderedTexts[i].y + orderedTexts[i].height) - orderedTexts[j].y;
                    if ( diff > 0){
                        orderedTexts[i].y-=diff;
                    }
                }
            }
        }
    }

    function hideDialogs() {
        for(var k in texts){
            texts[k].opacity = 0;
        }
        if (images["dialog_forward"] !== undefined)
            images["dialog_forward"].opacity = 0;
        if (images["dialog_backward"] !== undefined)
            images["dialog_backward"].opacity = 0;
    }

    Controller {
        id: game

        onCurrentFrameChanged: {
            var component;
            var object;
            hideDialogs();
            for (var i = 0; i < currentFrame.length; ++i){
                var f = currentFrame[i];
                if (f.isText()){
                    if (texts[f.id] !== undefined){
                        U.updateObject(texts[f.id],
                                       f.x,
                                       f.y,
                                       f.width,
                                       texts[f.id].height,
                                       f.alpha);
                        if (texts[f.id].text !== f.contnet)
                            texts[f.id].text = f.content;
                        continue;
                    }
                    component = Qt.createComponent("GameText.qml");
                    object = component.createObject(window,
                                                    {"x": f.x,
                                                     "y": f.y,
                                                     "width": f.width,
                                                     "alpha": f.alpha,
                                                     "text": f.content});
                    texts[f.id] = object;
                    continue;
                }
                if (images[f.id] !== undefined){
                    U.updateObject(images[f.id], f.x, f.y, f.width, f.height, f.alpha);
                    continue;
                }
                component = Qt.createComponent("GameImage.qml");
                object = component.createObject(window,
                                                {"x": f.x,
                                                 "y":f.y,
                                                 "width": f.width,
                                                 "height": f.height,
                                                 "opacity": f.alpha,
                                                 "source": "assets:/%1".arg(f.content)});
                images[f.id] = object;
            }
            disposeTexts();
        }

        onRoomChanged: {
            for(var k in images){
                images[k].destroy();
            }
            images = new Object;

            for(var j in texts){
                texts[j].destroy();
            }
            texts = new Object;
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
