#include <vector>
#include "map.h"
using namespace std;

#define blank    -1
#define corridor 0
#define wall     1

Map::Map(int a, int b){
    heigth = a;
    width  = b;
}

void Map::print(){
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < width; j++)
            if (map[i][j] == wall) cout << "#";
            else cout << "·";
        cout << endl;
    }
}

void Map::generate(){
    srand(time(NULL));
    outside();
    inside();
    mirror();
    middle();
}

void Map::outside(){
    for (int i = 0; i < heigth; i++) {
        vector<int> aux(width, wall);
        for (int j = 0; j < ceil(width / 2.0); j++)
            aux[j] = (i == 0 || i == heigth - 1 || j == 0 || j == width - 1 ) ? wall : blank;
        map.push_back(aux);
    }
    map[1][1] = corridor;
}

void Map::inside(){
    for (int i = 1; i < heigth - 1; i++)
        for (int j = 1; j < floor(width / 2.0); j++) {
            map[i][j] = getRandom();
            if (!check(i, j)) change(i, j);
        }
}

void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++)
        for (int j = 0; j < floor(width / 2.0); j++)
            map[i][width - 1 - j] = map[i][j];
}

void Map::middle(){
    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            map[i][floor(width / 2.0)] = corridor;
    }
}

/*
 * Comprovamos si es corredor
 * Comprovamos arriba
 * Comprovamos anterior
 */
bool Map::check(int i, int j){
    return (map[i][j] == corridor) ||
           (i != 1 && disparar(i, j - 1)) && // left
           (j != 1 && disparar(i - 1, j));   // up
}

bool Map::disparar(int i, int j){
    if (map[i][j] == wall) return true;

    int cont = 0;
    // up
    if (map[i - 1][j] == wall) cont++;
    // down
    if (map[i + 1][j] == wall) cont++;
    // left
    if (map[i][j - 1] == wall) cont++;
    // right
    if (map[i][j + 1] == wall) cont++;

    return cont < 3;
}

int Map::getRandom(){
    return (rand() % 100 <= 40) ? corridor : wall;
}

void Map::change(int i, int j){
    map[i][j] = corridor;
}
