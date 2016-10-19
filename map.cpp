#include "wall.h"
#include "corridor.h"
#include "map.h"
#include <stack>
using namespace std;

#define U 1
#define D 2
#define L 3
#define R 4

// Constructors
Map::Map(){ }

Map::Map(int a, int b){
    heigth = a;
    width  = b;
    generate();
}

Map::Map(char fname[]){ getMapFromFile(fname); }

// Getters
int Map::getHeigth(){ return heigth; }

int Map::getWidth(){ return width; }

vector<vector<Cell *> > Map::getMap(){ return map; }

// Methods
void Map::generate(){
    srand(time(NULL));
    populationCells();
    connectCells();
    inside();
    middle();
    inferiorRandom();
    middleRandom();
    mirror();
}

// Print
void Map::print(){ print(map); }

/*
 * Create and put all cells in the Vector<<Vector<Cell>>
 */
void Map::populationCells(){
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < width; j++)
            aux.push_back(new Wall(i, j));
        map.push_back(aux);
    }
}

/*
 * Connect the Cells - Top, Left, Right, Bottom.
 */
void Map::connectCells(){
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < ceil(width / 2.0); j++) {
            connect(map[i][j]);
        }
    }
}

void Map::connect(Cell * c){
    if ((c->getX() - 1) >= 0) c->setUp(&map[c->getX() - 1][c->getY()]);
    if ((c->getX() + 1) <= heigth - 1) c->setDown(&map[c->getX() + 1][c->getY()]);
    if ((c->getY() - 1) >= 0) c->setLeft(&map[c->getX()][c->getY() - 1]);
    if ((c->getY() + 1) <= width + 1) c->setRight(&map[c->getX()][c->getY() + 1]);
}

void Map::inside(){
    visited = getWhitePositionCells();

    int h = visited.size();
    int w = visited[0].size();

    // Primeiro elemento visitado.
    Cell * position = randomCellPosition(visited);
    position->setVisited(true);
    int quantidadeVisitados = 1;

    stack<Cell *> stack;

    while (quantidadeVisitados < h * w) {
        position = randomDiscoverPath(position);

        if (position == NULL) {
            position = stack.top();
            stack.pop();
        } else if (!position->isVisited()) {
            position->setVisited(true);
            stack.push(position);
            quantidadeVisitados++;
        }
    }
} // inside

void Map::middle(){
    int mid = floor(width / 2.0);

    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            changeToCorridor(map[i][mid]);
    }
}

void Map::inferiorRandom(){
    if (heigth % 2 == 0) {
        vector<Cell *> inferior = visited[visited.size() - 1];
        vector<int> shuffle;
        int nums = inferior.size();

        for (int i = 0; i < nums; i++) shuffle.push_back(i);
        random_shuffle(shuffle.begin(), shuffle.end());

        for (int i = 0; i < (int) shuffle.size() * 0.6; i++) {
            Cell * temp = *inferior[shuffle[i]]->getDown();
            changeToCorridor(temp);
            randomLeftRightInferior(temp);
        }
    }
}

bool Map::randomLeftRightInferior(Cell * c){
    vector<int> shuffle;
    Cell * tempCell = NULL;
    int x, y;

    for (int i = L; i <= R; i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 0; i < shuffle.size(); i++) {
        if ((shuffle[i] == L) && ((*c->getLeft())->getY() >= 1)) { // 3
            changeToCorridor(*c->getLeft());
            return true;
        } else if ((shuffle[i] == R) && ((*c->getRight())->getY() <= floor(width / 2))) { // 4
            changeToCorridor(*c->getRight());
            return true;
        }
    }
    return false;
}

void Map::middleRandom(){
    if ((width - 2) % 4 == 0) {
        vector<Cell *> middle;
        vector<int> shuffle;

        for (int i = 0; i < visited.size(); ++i) {
            middle.push_back(visited[i][visited[0].size() - 1]);
        }

        int nums = middle.size();
        for (int i = 0; i < nums; i++) shuffle.push_back(i);
        random_shuffle(shuffle.begin(), shuffle.end());

        for (int i = 0; i < shuffle.size() * 0.6; ++i) {
            Cell * temp = *middle[shuffle[i]]->getRight();
            changeToCorridor(temp);
            randomLeftRightMiddle(temp);
        }
    }
}

bool Map::randomLeftRightMiddle(Cell * c){
    vector<int> shuffle;
    Cell * tempCell = NULL;
    int x, y;

    for (int i = U; i <= D; i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 0; i < shuffle.size(); i++) {
        if ((shuffle[i] == U) && ((*c->getUp())->getX() >= 1)) { // 3
            changeToCorridor(*c->getUp());
            return true;
        } else if ((shuffle[i] == D) && ((*c->getDown())->getX() <= heigth - 2)) { // 4
            changeToCorridor(*c->getDown());
            return true;
        }
    }
    return false;
}

void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++) {
        for (int j = floor(width / 2.0) - 1; j >= 0; j--) {
            map[i][width - j - 1] = map[i][j];
        }
    }
}

bool Map::insideCondition(int x, int y){
    return (x >= 0 && x < (visited.size())) && (y >= 0 && y < visited[0].size());
}

void Map::changeToCorridor(Cell * cell){
    int x, y;

    x = cell->getX();
    y = cell->getY();

    Cell * corredor = new Corridor(x, y);
    corredor->setVisited(cell->isVisited());
    corredor->setUp(cell->getUp());
    corredor->setDown(cell->getDown());
    corredor->setLeft(cell->getLeft());
    corredor->setRight(cell->getRight());
    map[x][y] = corredor;
}

vector<vector<Cell *> > Map::getWhitePositionCells(){
    int decision;

    vector<vector<Cell *> > visited;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;

        if (width % 2 == 0)
            decision = floor(width / 2.0);
        else
            decision = floor(width / 2.0) + 1;

        for (int j = 1; j < decision; j += 2) {
            changeToCorridor(map[i][j]);
            aux.push_back(map[i][j]);
        }
        visited.push_back(aux);
    }

    return visited;
}

Cell * Map::randomCellPosition(vector<vector<Cell *> > visited){
    // Size Height and Width visited'list.
    int h = visited.size();
    int w = visited[0].size();

    int randX, randY;

    randX = rand() % (w + 1);
    randY = rand() % (int) (floor((h + 1) / 2.0));

    int in = 0;
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[0].size(); j++) {
            if (!visited[i][j]->isVisited()) {
                return visited[i][j];
            }
        }
    }
    return NULL;
}

Cell * Map::randomDiscoverPath(Cell * c){
    vector<int> shuffle;
    Cell * tempCell = NULL;
    int x, y;


    for (int i = 1; i <= 4; i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 0; i < shuffle.size(); i++) {
        x = floor((c->getX() - 1) / 2.0);
        y = floor((c->getY() - 1) / 2.0);
        if ((shuffle[i] == U) && (insideCondition(x - 1, y))) { // 1
            x--;
            tempCell = *c->getUp();
        } else if ((shuffle[i] == D) && (insideCondition(x + 1, y))) { // 2
            x++;
            tempCell = *c->getDown();
        } else if ((shuffle[i] == L) && (insideCondition(x, y - 1))) { // 3
            y--;
            tempCell = *c->getLeft();
        } else if ((shuffle[i] == R) && (insideCondition(x, y + 1))) { // 4
            y++;
            tempCell = *c->getRight();
        }
        if (!visited[x][y]->isVisited()) {
            changeToCorridor(tempCell);
            return visited[x][y];
        }
    }
    return NULL;
} // randomDiscoverPath

void Map::getMapFromFile(char * fname){
    string s = "";
    string saux;
    ifstream in(fname); // Open for reading

    while (getline(in, saux)) {
        if (s == "") width = saux.size();
        s += saux;
    }
    heigth = s.size() / width;
    int w = 0;
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < width; j++) {
            if (s[w] == '0') {
                aux.push_back(new Wall(i, j));
            } else if (s[w] == '.') {
                aux.push_back(new Corridor(i, j));
            }
            w++;
        }
        map.push_back(aux);
    }
}

void Map::print(vector<vector<Cell *> > v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j]->getSymbol();
        }
        cout << endl;
    }
    cout << endl;
}
