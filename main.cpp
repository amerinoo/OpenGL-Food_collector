#include <iostream>
#include <GL/glut.h>
#include "graphics.h"
using namespace std;

int main(int argc, char * argv[]){
    int heigth;
    int width;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <heigth> <width>" << std::endl;
        return -1;
    }
    heigth = atoi(argv[1]);
    width  = atoi(argv[2]);

    Map map(heigth, width);
    map.print();

    Graphics& graphics = Graphics::getInstance();
    graphics.setMap(map);
    graphics.init(argc, argv);

    return 0;
}
