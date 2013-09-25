function click(x, y) {
    window.hideDialogs();
    var coords = mapToItem(window, x, y);
    game.click(coords.x, coords.y);
}
