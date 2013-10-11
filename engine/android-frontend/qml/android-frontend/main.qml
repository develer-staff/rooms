import QtQuick 2.0
import rooms 1.0
import "utils.js" as U

Rectangle {
    id: window
    width: 360
    height: 360


    onWidthChanged: {
        game.windowWidth = width;
    }

    onHeightChanged: {
        game.windowHeight = height;
    }

    property var images: new Object;
    property var texts: new Object;

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
                                       f.y + (f.height / 2),
                                       f.width,
                                       f.height,
                                       f.alpha);
                        continue;
                    }
                    component = Qt.createComponent("GameText.qml");
                    object = component.createObject(window,
                                                    {"x": f.x,
                                                     "y": f.y + (f.height / 2),
                                                     "width": f.width,
                                                     "height": f.height,
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
