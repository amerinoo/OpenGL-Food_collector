#include "wall.h"
#include "corridor.h"
#include "map.h"
#include <stack>
using namespace std;

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

Map::Map(){ }

Map::Map(int a, int b){
    heigth = a;
    width  = b;
}

Map::Map(vector<vector<Cell *> > m){
    map = m;
}

vector<vector<Cell *> > Map::getMap(){
    return map;
}

void Map::print(){
    print(map);
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

void Map::generate(){
    srand(time(NULL));
    populationCells();
    connectCells();
    inside(); 
 
    print(); 
 
    if(heigth%2==0) 
        inferiorRandom(); 
 
    if(width%4==0) 
        middle(); 
    else if(width%2 == 0) 
        middleRandom(); 

    mirror();
}

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
    // Top
    if ((c->getX() - 1) >= 0) {
        c->top = &map[c->getX() - 1][c->getY()];
    }
    // Bottom
    if ((c->getX() + 1) <= heigth - 1) {
        c->bottom = &map[c->getX() + 1][c->getY()];
    }
    // Left
    if ((c->getY() - 1) >= 0) {
        c->left = &map[c->getX()][c->getY() - 1];
    }
    // Rigth
    if ((c->getY() + 1) <= width + 1) {
        c->right = &map[c->getX()][c->getY() + 1];
    }
}

void Map::changeToCorridor(Cell * cell){
    int x, y;

    x = cell->getX();
    y = cell->getY();

    Cell * corredor = new Corridor(x, y);
    corredor->setVisited(cell->isVisited());
    corredor->top    = cell->top;
    corredor->bottom = cell->bottom;
    corredor->left   = cell->left;
    corredor->right  = cell->right;
    map[x][y]        = corredor;
}

vector<vector<Cell *> > Map::getWhitePositionCells(){
    int decision;
    vector<vector<Cell *> > visited;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;

        if(width%2==0) 
            decision = floor(width/2.0); 
        else 
            decision = floor(width/2.0)+1; 
 
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
            std::cout << "NULL" << std::endl;
            position = stack.top();
            stack.pop();
        } else if (!position->isVisited()) {
            position->setVisited(true);
            stack.push(position);
            quantidadeVisitados++;
        }
    }
} // inside

Cell * Map::randomDiscoverPath(Cell * c){
    vector<int> shuffle;
    Cell * tempCell = NULL;
    int x, y;


    for (int i = 1; i <= 4; i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 0; i < shuffle.size(); i++) {
        x = floor((c->getX() - 1) / 2.0);
        y = floor((c->getY() - 1) / 2.0);
        if ((shuffle[i] == UP) && (insideCondition(x - 1, y))) { // 1
            x--;
            tempCell = *c->top;
        } else if ((shuffle[i] == DOWN) && (insideCondition(x + 1, y))) { // 2
            x++;
            tempCell = *c->bottom;
        } else if ((shuffle[i] == LEFT) && (insideCondition(x, y - 1))) { // 3
            y--;
            tempCell = *c->left;
        } else if ((shuffle[i] == RIGHT) && (insideCondition(x, y + 1))) { // 4
            y++;
            tempCell = *c->right;
        }
        if (!visited[x][y]->isVisited()) {
            changeToCorridor(tempCell);
            return visited[x][y];
        }
    }
    return NULL;
} // randomDiscoverPath

bool Map::insideCondition(int x, int y){
    return (x >= 0 && x < (visited.size())) && (y >= 0 && y < visited[0].size());
}

void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++) {
        for (int j = floor(width / 2.0) - 1; j >= 0; j--) {
            map[i][width - j - 1] = map[i][j];
        }
    }
}


void Map::inferiorRandom(){ 
    cout << "Inferior Random " << endl; 
    vector<Cell *> inferior = visited[visited.size()-1]; 
    vector<int> shuffle; 
    int nums = inferior.size(); 
 
    for (int i = 0; i < nums; i++) shuffle.push_back(i); 
    random_shuffle(shuffle.begin(), shuffle.end()); 
 
    for (int i = 0; i < (int)shuffle.size()*0.6; i++) 
    { 
        Cell *temp = * inferior[shuffle[i]]->bottom; 
        changeToCorridor(temp); 
        randomLeftRightInferior(temp); 
    } 
} 
 
bool Map::randomLeftRightInferior(Cell * c){ 
    vector<int> shuffle; 
    Cell * tempCell = NULL; 
    int x, y; 
 
    for (int i = LEFT; i <= RIGHT; i++) shuffle.push_back(i); 
    random_shuffle(shuffle.begin(), shuffle.end()); 
    cout << endl; 
    c->toString(); 
    for (int i = 0; i < shuffle.size(); i++) { 
        cout << "Valor de Y:" << c->getY() << endl; 
        if ((shuffle[i] == LEFT) && ((*c->left)->getY()>=1)) { // 3 
            cout << "Entrou left "; 
            (*c->left)->toString(); 
            changeToCorridor(*c->left); 
            return true; 
        } else if ((shuffle[i] == RIGHT) && ((*c->right)->getY()<=floor(width/2))) { // 4 
            cout << "Entrou right "; 
            (*c->right)->toString(); 
            changeToCorridor(*c->right); 
            return true; 
        } 
    } 
    return false; 
} 
 
 
void Map::middleRandom(){ 
    cout << "Middle Random " << endl; 
    vector<Cell *> middle; 
    vector<int> shuffle; 
 
    for (int i = 0; i < visited.size(); ++i) 
    { 
        middle.push_back(visited[i][visited[0].size()-1]); 
    } 
 
    int nums = middle.size(); 
    for (int i = 0; i < nums; i++) shuffle.push_back(i); 
    random_shuffle(shuffle.begin(), shuffle.end()); 
 
    for (int i = 0; i < shuffle.size()*0.6; ++i) 
    { 
        Cell *temp = * middle[shuffle[i]]->right; 
        changeToCorridor(temp); 
        randomLeftRightMiddle(temp); 
    } 
} 
 
bool Map::randomLeftRightMiddle(Cell * c){ 
    vector<int> shuffle; 
    Cell * tempCell = NULL; 
    int x, y; 
 
    for (int i = UP; i <= DOWN; i++) shuffle.push_back(i); 
    random_shuffle(shuffle.begin(), shuffle.end()); 
    cout << endl; 
    c->toString(); 
    for (int i = 0; i < shuffle.size(); i++) { 
        cout << "Valor de Y:" << c->getY() << endl; 
        if ((shuffle[i] == UP) && ((*c->top)->getX()>=1)) { // 3 
            cout << "Entrou left "; 
            changeToCorridor(*c->top); 
            return true; 
        } else if ((shuffle[i] == DOWN) && ((*c->bottom)->getX()<=heigth-2)) { // 4 
            cout << "Entrou right "; 
            (*c->right)->toString(); 
            changeToCorridor(*c->bottom); 
            return true; 
        } 
    } 
    return false; 
} 

void Map::middle(){
    int mid = floor(width / 2.0);

    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            changeToCorridor(map[i][mid]);
    }
}
