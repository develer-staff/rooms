function click(x, y) {
    var coords = mapToItem(window, x, y);
    game.click(coords.x, coords.y);
}

function updateObject(obj, x, y, w, h, a){
    obj.x = x;
    obj.y = y;
    obj.width = w;
    obj.height = h;
    obj.opacity = a;
}
