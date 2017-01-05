/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "map.h"
using namespace std;

const int Map::initX = 1;
const int Map::initY = 1;
float Map::seed      = 1;
bool Map::isSeed     = false;

// Constructors
Map::Map(){ }

Map::Map(int height, int width)
    : height(height), width(width){
    scorePlayer = 0;
    scoreEnemy  = 0;
    totalFood   = -2;
}

Map::Map(char fname[]){ getMapFromFile(fname); }

// Getters
int Map::getHeight(){ return height; }

int Map::getWidth(){ return width; }

void Map::setSeed(float seed){
    this->isSeed = true;
    this->seed   = seed;
}

float Map::getSeed(){
    return (this->isSeed) ? this->seed : rand();
}

vector<vector<Cell *> > Map::getMap(){ return map; }

string Map::toString(){
    ostringstream mapString;

    for (unsigned int i = 0; i < map.size(); i++) {
        for (unsigned int j = 0; j < map[i].size(); j++) {
            mapString << map[i][j]->getSymbol() << " ";
        }
        mapString << endl;
    }
    return mapString.str();
}

// Methods
void Map::generate(){
    srand(getSeed());
    initCells();
    connectCells();
    inside();
    middle();
    inferiorRandom();
    middleRandom();
    mirror();
    connectCells();
    initMap();
}

void Map::initMap(){
    for (unsigned int i = 0; i < map.size(); i++)
        for (unsigned int j = 0; j < map[0].size(); j++)
            if (map[i][j]->isCorridor()) {
                map[i][j]->setCellType(FOOD);
                totalFood += 1;
            }
}

Cell * Map::getInitPosition(CellType agent){
    return (agent == PLAYER) ? map[Map::initX][Map::initY] : map[Map::initX][width - 1 - Map::initY];
}

void Map::setPosition(CellType agent, Cell * c){
    if (agent == PLAYER) {
        player = c;
    } else {
        enemy = c;
    }
}

/*
 * Create and put all cells in the Vector<<Vector<Cell>>
 */
void Map::initCells(){
    for (int i = 0; i < height; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < ceil(width / 2.0); j++)
            aux.push_back(new Cell(i, j, WALL));
        map.push_back(aux);
    }
}

/*
 * Connect the Cells - Top, Left, Right, Bottom.
 */
void Map::connect(Cell * c){
    if ((c->getX() - 1) >= 0) c->setUp(map[c->getX() - 1][c->getY()]);
    if ((c->getX() + 1) <= height - 1) c->setDown(map[c->getX() + 1][c->getY()]);
    if ((c->getY() - 1) >= 0) c->setLeft(map[c->getX()][c->getY() - 1]);
    if ((c->getY() + 1) <= width + 1) c->setRight(map[c->getX()][c->getY() + 1]);
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
    for (int i = 1; i < height - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j < decision; j += 2) {
            map[i][j]->setCellType(CORRIDOR);
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
            tempCell = c->getUp();
        } else if ((shuffle[i] == DOWN) && (insideCondition(x + 1, y))) {
            x++;
            tempCell = c->getDown();
        } else if ((shuffle[i] == LEFT) && (insideCondition(x, y - 1))) {
            y--;
            tempCell = c->getLeft();
        } else if ((shuffle[i] == RIGHT) && (insideCondition(x, y + 1))) {
            y++;
            tempCell = c->getRight();
        }
        if (!visited[x][y]->isVisited()) {
            tempCell->setCellType(CORRIDOR);
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
    vector<Direction> shuffle;
    shuffle.push_back(UP);
    shuffle.push_back(DOWN);
    shuffle.push_back(LEFT);
    shuffle.push_back(RIGHT);
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
            openRandom(position, shuffle);
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
        for (int i = 1; i < height - 1; i++)
            map[i][mid]->setCellType(CORRIDOR);
    }
}

/*
 * Put randoms in the wall inferiors to have path.
 */
void Map::inferiorRandom(){
    if (height % 2 == 0) {
        vector<Cell *> inferior = visited[visited.size() - 1];
        vector<int> shuffle;
        int nums = inferior.size();

        vector<Direction> directions;
        directions.push_back(LEFT);
        directions.push_back(RIGHT);

        for (int i = 0; i < nums; i++) shuffle.push_back(i);
        random_shuffle(shuffle.begin(), shuffle.end());

        for (int i = 0; i < (int) shuffle.size() * 0.6; i++) {
            Cell * temp = inferior[shuffle[i]]->getDown();
            temp->setCellType(CORRIDOR);
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
            Cell * temp = middle[shuffle[i]]->getRight();
            temp->setCellType(CORRIDOR);
            openRandom(temp, directions);
        }
    }
}

/*
 * If analyze middle will be checking top and bottom if have one connection,
 * if analyze inferior will be checking left and right.
 */
void Map::openRandom(Cell * c, vector<Direction> directions){
    if (directions.size() > 0) {
        random_shuffle(directions.begin(), directions.end());
        int i = 0;
        if ((directions[i] == UP) && (c->getUp()->getX() >= 1)) {
            c->getUp()->setCellType(CORRIDOR);
        } else if ((directions[i] == DOWN) && (c->getDown()->getX() <= height - 2)) {
            c->getDown()->setCellType(CORRIDOR);
        } else if ((directions[i] == LEFT) && (c->getLeft()->getY() >= 1)) {
            c->getLeft()->setCellType(CORRIDOR);
        }
    }
}

vector<Direction> Map::getLegalActions(Cell * c){
    vector<Direction> legalActions;

    if (!c->getUp()->isWall()) legalActions.push_back(UP);
    if (!c->getDown()->isWall()) legalActions.push_back(DOWN);
    if (!c->getLeft()->isWall()) legalActions.push_back(LEFT);
    if (!c->getRight()->isWall()) legalActions.push_back(RIGHT);

    return legalActions;
}

Map Map::generateSuccessor(CellType agent, Direction action){
    Map other(*this);

    other.setPosition(agent, getNextState(getPosition(agent), action));
    if (agent == PLAYER) {
        other.scorePlayer -= 1;
    } else {
        other.scoreEnemy -= 1;
    }
    if (other.getPosition(agent)->hasFood()) other.eat(agent);
    return other;
}

Cell * Map::getNextState(Cell * cell, Direction direction){
    if (direction == UP) return cell->getUp();
    else if (direction == DOWN) return cell->getDown();
    else if (direction == LEFT) return cell->getLeft();
    else return cell->getRight();
}

/*
 * Logic the mirror the matriz.
 */
void Map::mirror(){
    for (int i = 0; i <= height - 1; i++)
        for (int j = floor(width / 2.0) - 1; j >= 0; j--) {
            Cell * cell = map[i][j];

            if (cell->isCorridor()) {
                map[i].push_back(new Cell(i, width - j - 1, CORRIDOR));
            } else if (cell->isWall()) {
                map[i].push_back(new Cell(i, width - j - 1, WALL));
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
    height = s.size() / width;
    int w = 0;
    for (int i = 0; i < height; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < width; j++) {
            if (s[w] == '0') {
                aux.push_back(new Cell(i, j, WALL));
            } else if (s[w] == '.') {
                aux.push_back(new Cell(i, j, CORRIDOR));
            }
            w++;
        }
        map.push_back(aux);
    }
}

vector<Cell *> Map::getFood(){
    vector<Cell *> listCell;

    for (unsigned int i = 0; i < map.size(); i++)
        for (unsigned int j = 0; j < map[i].size(); j++)
            if (map[i][j]->hasFood())
                listCell.push_back(map[i][j]);

    return listCell;
}

vector<Cell *> Map::getCandidateFood(){
    vector<Cell *> listCell;
    vector<Cell *> foods = getFood();

    for (unsigned int i = 0; i < foods.size(); i++)
        if (isCandidate(foods[i]))
            listCell.push_back(foods[i]);

    return listCell;
}

bool Map::isCandidate(Cell * c){
    if (c->getUp()->isCorridor()) return true;
    else if (c->getDown()->isCorridor()) return true;
    else if (c->getLeft()->isCorridor()) return true;
    else if (c->getRight()->isCorridor()) return true;

    return false;
}

int Map::getScore(CellType agent){
    return (agent == PLAYER) ? scorePlayer : scoreEnemy;
}

Cell * Map::getPosition(CellType agent){
    return (agent == PLAYER) ? player : enemy;
}

bool Map::isInInitialPosition(CellType agent){
    return getInitPosition(agent) == getPosition(agent);
}

int Map::getFoodRemaining(){ return totalFood; }

bool Map::hasFood(){ return totalFood != 0; }

void Map::eat(CellType agent){
    incrementScore(agent);
    totalFood -= 1;
}

void Map::incrementScore(CellType agent){
    int multiplier = 10;

    if (agent == PLAYER) {
        scorePlayer += 1 * multiplier;
    } else {
        scoreEnemy += 1 * multiplier;
    }
}
