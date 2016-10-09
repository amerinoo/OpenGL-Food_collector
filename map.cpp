#include "map.h"
#include "wall.h"
#include "corridor.h"
using namespace std;

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3


Map::Map(int a, int b){
    heigth = a;
    width  = b;
}

void Map::print(){
    print(map);
}

void Map::print(vector<vector<Cell *> > v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j]->type() == 1) cout << "#";
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
    vector<vector<Cell *> > visited;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j < floor(width / 2.0); j += 2) {
            map[i][j] = new Corridor(i, j);
            aux.push_back(map[i][j]);
        }
        visited.push_back(aux);
    }
    int h = visited.size();
    int w = visited[0].size();
    Cell * c;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            c = visited[i][j];
            vector<Cell *> neighbours = c->getNeighbours();
            if (i - 1 >= 0) neighbours.push_back(visited[i - 1][j]);  // Left
            if (i + 1 < w) neighbours.push_back(visited[i + 1][j]);   // Right
            if (j - 1 >= 0) neighbours.push_back(visited[i][j - 1]);  // Up
            if (j + 1 < h) neighbours.push_back(visited[i][j + 1]);   // Down
            std::cout << c->getNeighbours().size() << std::endl;
        }
    }
    int numVisited = 1;
    stack<Cell *> path;
    c = visited[0][0];
    // std::cout << c->getNeighbours().size() << std::endl;
    while (numVisited < h * w) {
        // test(visited);
        if (hasValidNeighbours(c)) {
            std::cout << "if" << std::endl;
            int direction;
            do {
                direction = getRandomDirection();
                cout << direction;
            } while (isValid(direction));
        } else {
            // c = path.top();
            // path.pop();
        }
        numVisited++;
    }
    print();
} // inside

bool Map::hasValidNeighbours(Cell * c){
    vector<Cell *> neighbours = c->getNeighbours();
    // std::cout << neighbours.size() << std::endl;
    for (int i = 0; i < neighbours.size(); i++) {
        std::cout << neighbours[i]->isVisited() << std::endl;
        if (!neighbours[i]->isVisited()) {
            return true;
        }
    }
    return false;
}

bool Map::isValid(int direction){
    if (direction == LEFT) {
        return false;
    } else if (direction == RIGHT) {
        return false;
    } else if (direction == UP) {
        return false;
    } else if (direction == DOWN) {
        return false;
    }
    return false;
}

void Map::test(vector<vector<Cell *> > v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j]->isVisited() << " ";
        }
        cout << endl;
    }
    cout << endl;
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

int Map::getRandomDirection(){
    return rand() % 4;
}
