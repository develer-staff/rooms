import QtQuick 2.0
import rooms 1.0

Rectangle {
    id: window
    width: game.windowWidth
    height: game.windowHeight

    onWidthChanged: {
        game.windowWidth = width;
    }

    onHeightChanged: {
        game.windowHeight = height;
    }

    property var images: new Object;
    property var texts: new Object;
    property var toHide: new Array;

    function hideDialogs() {
        for(var k in texts){
            toHide.push(texts[k]);
        }
        if (images["dialog_forward"] !== undefined)
            toHide.push(images["dialog_forward"])
        if (images["dialog_backward"] !== undefined)
            toHide.push(images["dialog_backward"])
    }

    Controller {
        id: game

        onDrawImage: {
            if(images[id] !== undefined){
                images[id].x = x;
                images[id].y = y;
                images[id].width = w;
                images[id].height = h;
                images[id].opacity = alpha;
                images[id].cursorShape = Qt.ArrowCursor;
            } else {
                var component = Qt.createComponent("GameImage.qml");
                var object = component.createObject(window, {"x":x, "y":y, "width":w, "height":h, "opacity": alpha,
                                                        "source":"../../"+image});

                images[id] = object;
            }
        }

        onDrawText: {
            while(toHide.length > 0){
                toHide.pop().opacity = 0;
            }
            if (texts[id] !== undefined){
                texts[id].x = x;
                texts[id].y = y+h/2;
                texts[id].width = w;
                texts[id].height = h;
                texts[id].opacity = 1;
                return;
            }
            var component = Qt.createComponent("GameText.qml");
            var object = component.createObject(window, {"x":x, "y":y+h/2, "width":w, "height":h, "text":text});

            texts[id] = object;
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

        onStateChanged: {
            if(state !== Controller.DIALOG){
                while(toHide.length > 0){
                    toHide.pop().opacity = 0;
                }
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
