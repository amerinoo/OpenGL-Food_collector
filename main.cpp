/*
 * Project name: Food collection
 * Version 3
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include "graphics.h"
#include "drawer.h"
using namespace std;

bool
hasCorrectArguments(int, int, int, int);

int main(int argc, char * argv[]){
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <height> <width>" << endl;
        return -1;
    }

    Graphics& graphics = Graphics::getInstance();
    graphics.init(argc, argv);
    int height    = atoi(argv[1]);
    int width     = atoi(argv[2]);
    int maxHeight = graphics.getMaxHeight();
    int maxWidth  = graphics.getMaxWidth();

    if (hasCorrectArguments(height, width, maxHeight, maxWidth)) {
        cout << "Error: Ilegal Arguments" << endl;
        cout << "Usage: " << argv[0] << " <height> <width>" << endl;
        cout << "Height must be larger than 3 and smaller than " << maxHeight << endl;
        cout << "width must be larger than 3 and smaller than " << maxWidth << endl;
        return -1;
    }

    Game game(height, width);

    Drawer& drawer = Drawer::getInstance();
    drawer.setHeight(height);
    drawer.setWidth(width);

    graphics.setGame(game);
    graphics.start();

    return 0;
}

bool hasCorrectArguments(int height, int width, int maxHeight, int maxWidth){
    return height < 3 || width < 3 || height > maxHeight || width > maxWidth;
}
