/*
 * Project name: Food collection
 * Version 2
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include <iostream>
#include "graphics.h"
using namespace std;

bool
hasCorrectArguments(int, int, int, int);

int main(int argc, char * argv[]){
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <heigth> <width>" << endl;
        return -1;
    }

    Graphics& graphics = Graphics::getInstance();
    graphics.init(argc, argv);
    int heigth    = atoi(argv[1]);
    int width     = atoi(argv[2]);
    int maxHeigth = graphics.getMaxHeigth();
    int maxWidth  = graphics.getMaxWidth();

    if (hasCorrectArguments(heigth, width, maxHeigth, maxWidth)) {
        cout << "Error: Ilegal Arguments" << endl;
        cout << "Usage: " << argv[0] << " <heigth> <width>" << endl;
        cout << "Heigth must be larger than 3 and smaller than " << maxHeigth << endl;
        cout << "width must be larger than 3 and smaller than " << maxWidth << endl;
        return -1;
    }

    Game game(heigth, width);

    graphics.setGame(game);
    graphics.start();

    return 0;
}

bool hasCorrectArguments(int heigth, int width, int maxHeigth, int maxWidth){
    return heigth < 3 || width < 3 || heigth > maxHeigth || width > maxWidth;
}
