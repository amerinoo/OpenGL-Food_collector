/*
 * Project name: Food collection
 * Version 1
 * Student 1: Albert Eduard Merino Pulido
 * Student 2: Tan Kin Tat
 */
#include "map.h"
using namespace std;

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
    initCells();
    connectCells();
    inside();
    middle();
    inferiorRandom();
    middleRandom();
    mirror();
    connectCells();
}

// Print
void Map::print(){ print(map); }

/*
 * Create and put all cells in the Vector<<Vector<Cell>>
 */
void Map::initCells(){
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < ceil(width/2.0); j++)
            aux.push_back(new Wall(i, j));
        map.push_back(aux);
    }
}

/*
 * Connect the Cells - Top, Left, Right, Bottom.
 */
void Map::connect(Cell * c){
    if ((c->getX() - 1) >= 0) c->setUp(&map[c->getX() - 1][c->getY()]);
    if ((c->getX() + 1) <= heigth - 1) c->setDown(&map[c->getX() + 1][c->getY()]);
    if ((c->getY() - 1) >= 0) c->setLeft(&map[c->getX()][c->getY() - 1]);
    if ((c->getY() + 1) <= width + 1) c->setRight(&map[c->getX()][c->getY() + 1]);
}

/*
 * Analyze one by one the Cells use connect function.
 */
void Map::connectCells(){
    for (unsigned int i = 0; i < map.size(); i++) {
        for (unsigned int j = 0; j < map[0].size(); j++) {
            connect(map[i][j]);
        }
    }
}

/*
 * Logic to put the white positions
 * Ex: 11111
 *     10101
 *     11111
 *     10101
 *     11111
 */
void Map::initWhitePositionCells(){
    int decision;

    decision = floor(width / 2.0);
    if (width % 2 != 0) decision += 1;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j < decision; j += 2) {
            changeToCorridor(map[i][j]);
            aux.push_back(map[i][j]);
        }
        visited.push_back(aux);
    }
}

/*
 * Will random the for positions and look which position choose. (top/bottom/left/right)
 */
Cell * Map::randomDiscoverPath(Cell * c){
    Cell * tempCell = NULL;
    int x, y;

    vector<Direction> shuffle;
    shuffle.push_back(UP);
    shuffle.push_back(DOWN);
    shuffle.push_back(LEFT);
    shuffle.push_back(RIGHT);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (unsigned int i = 0; i < shuffle.size(); i++) {
        x = floor((c->getX() - 1) / 2.0);
        y = floor((c->getY() - 1) / 2.0);
        if ((shuffle[i] == UP) && (insideCondition(x - 1, y))) {
            x--;
            tempCell = *c->getUp();
        } else if ((shuffle[i] == DOWN) && (insideCondition(x + 1, y))) {
            x++;
            tempCell = *c->getDown();
        } else if ((shuffle[i] == LEFT) && (insideCondition(x, y - 1))) {
            y--;
            tempCell = *c->getLeft();
        } else if ((shuffle[i] == RIGHT) && (insideCondition(x, y + 1))) {
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

/*
 * Analyze all the white positions and get one random position (top/bottom/left/right) and change wall to corridor.
 * If don't have exit, will pop the previous positions to analyze again.
 */
void Map::inside(){
    initWhitePositionCells();

    int h = visited.size();
    int w = visited[0].size();

    // Primeiro elemento visitado.
    Cell * position = visited[0][0];
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

/*
 * If the map its odd put middle corridor.
 */
void Map::middle(){
    int mid = floor(width / 2.0);
    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            changeToCorridor(new Corridor(i, mid));
    }
}

/*
 * Put randoms in the wall inferiors to have path.
 */
void Map::inferiorRandom(){
    if (heigth % 2 == 0) {
        vector<Cell *> inferior = visited[visited.size() - 1];
        vector<int> shuffle;
        int nums = inferior.size();

        vector<Direction> directions;
        directions.push_back(LEFT);
        directions.push_back(RIGHT);

        for (int i = 0; i < nums; i++) shuffle.push_back(i);
        random_shuffle(shuffle.begin(), shuffle.end());

        for (int i = 0; i < (int) shuffle.size() * 0.6; i++) {
            Cell * temp = *inferior[shuffle[i]]->getDown();
            changeToCorridor(temp);
            openRandom(temp, directions);
        }
    }
}

/*
 * Put randoms in the wall middle to have path.
 */
void Map::middleRandom(){
    if ((width - 2) % 4 == 0) {
        vector<Cell *> middle;
        vector<int> shuffle;

        vector<Direction> directions;
        directions.push_back(UP);
        directions.push_back(DOWN);
        for (unsigned int i = 0; i < visited.size(); ++i) {
            middle.push_back(visited[i][visited[0].size() - 1]);
        }

        int nums = middle.size();
        for (int i = 0; i < nums; i++) shuffle.push_back(i);
        random_shuffle(shuffle.begin(), shuffle.end());

        for (int i = 0; i < shuffle.size() * 0.6; ++i) {
            Cell * temp = *middle[shuffle[i]]->getRight();
            changeToCorridor(temp);
            openRandom(temp, directions);
        }
    }
}

/*
 * If analyze middle will be checking top and bottom if have one connection,
 * if analyze inferior will be checking left and right.
 */
void Map::openRandom(Cell * c, vector<Direction> directions){
    random_shuffle(directions.begin(), directions.end());

    for (unsigned int i = 0; i < directions.size(); i++) {
        if ((directions[i] == UP) && ((*c->getUp())->getX() >= 1)) {
            changeToCorridor(*c->getUp());
            break;
        } else if ((directions[i] == DOWN) && ((*c->getDown())->getX() <= heigth - 2)) {
            changeToCorridor(*c->getDown());
            break;
        } else if ((directions[i] == LEFT) && ((*c->getLeft())->getY() >= 1)) {
            changeToCorridor(*c->getLeft());
            break;
        } else if ((directions[i] == RIGHT) && ((*c->getRight())->getY() <= floor(width / 2))) {
            changeToCorridor(*c->getRight());
            break;
        }
    }
}

/*
 * Logic the mirror the matriz.
 */
void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++)
        for (int j = floor(width / 2.0) - 1; j >= 0; j--){
            Cell* cell = map[i][j];

            if(cell->getType() == CORRIDOR){
                map[i].push_back(new Corridor(i, width-j-1));
            }else if(cell->getType() == WALL){
                map[i].push_back(new Wall(i, width-j-1));
            }
        }
}

/*
 * Function to analyze if the pointer its inside the matriz.
 */
bool Map::insideCondition(unsigned int x, unsigned int y){
    return (x >= 0 && x < (visited.size())) && (y >= 0 && y < visited[0].size());
}

/*
 * Change to Corridor function.
 */
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

/*
 * Receive one text path and store in the variable map.
 */
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

/*
 * Print.
 */
void Map::print(vector<vector<Cell *> > v){
    for (unsigned int i = 0; i < v.size(); i++) {
        for (unsigned int j = 0; j < v[i].size(); j++) {
            cout << v[i][j]->getSymbol();
        }
        cout << endl;
    }
    cout << endl;
}
