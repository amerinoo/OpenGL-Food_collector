#include <iostream>
#include "map.h"
using namespace std;

int main(int argc, char const * argv[]){
    int heigth;
    int width;

    if (argc < 3) {
        heigth = 10;
        width  = 24;
    } else {
        heigth = atoi(argv[1]);
        width  = atoi(argv[2]);
    }
    Map map(heigth, width);

    map.generate();
    // map.print();
    return 0;
}
