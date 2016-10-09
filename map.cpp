#include "map.h"
#include "wall.h"
#include "corridor.h"
using namespace std;

#define blank    -1
#define corridor 0
#define wall     1

Map::Map(int a, int b){
    heigth = a;
    width  = b;
}

void Map::print(){
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j]->type() == 1) cout << "#";
            else cout << "·";
        }
        cout << endl;
    }
    cout << endl;
}

void Map::generate(){
    srand(time(NULL));
    outside();
    inside();
    mirror();
    middle();
    // print();
}

void Map::outside(){
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < ceil(width / 2.0); j++)
            aux.push_back(new Wall(i, j));
        map.push_back(aux);
    }

    map[1][1] = new Corridor(1, 1);
}

void Map::inside(){
    vector<Cell *> unvisited;
    for (int i = 1; i < heigth - 1; i += 2)
        for (int j = 1; j < floor(width / 2.0); j += 2) {
            map[i][j] = new Corridor(i, j);
            unvisited.push_back(map[i][j]);
        }
    print();

    cout << getRandom() << endl;

    print();
}

void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++)
        for (int j = width / 2.0 - 1; j >= 0; j--)
            map[i].push_back(map[i][j]);
}

void Map::middle(){
    int mid = floor(width / 2.0);

    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            map[i][mid] = new Corridor(i, mid);
    }
}

int Map::getRandom(){
    return rand() % 4 + 1;
}
