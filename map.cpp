#include "wall.h"
#include "corridor.h"
#include "map.h"
#include <stack>
using namespace std;

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4


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
            cout << v[i][j]->getSymbol();
        }
        cout << endl;
    }
    cout << endl;
}

void Map::printV(vector<vector<Cell *> > v){
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j]->isVisited()){
                cout << "X";
            }else{
                cout << "O";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Map::generate(){
    srand(time(NULL));
    populationCells();
    connectCells();
    //outside();
    inside();
    mirror();
    middle();
    print();
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
        for (int j = 0; j < ceil(width / 2.0); j++)
            map[i][j] = connect(map[i][j]);
    }
}

Cell* Map::connect(Cell *c){
    //Top
    if((c->getX() - 1) >= 0){
        c->top = &map[c->getX()-1][c->getY()];
    }
    //Bottom
    if((c->getX() + 1) <= heigth-1){
        c->bottom = &map[c->getX()+1][c->getY()];
    }
    //Left
    if((c->getY() - 1) >= 0){
        c->left = &map[c->getX()][c->getY()-1];
    }
    //Rigth
    if((c->getY() + 1) <= width+1){
        c->right = &map[c->getX()][c->getY()+1];
    }
    return c;
}

void Map::changeToCorridor(Cell *cell)
{
    int x,y;

    x = cell->getX();
    y = cell->getY();

    Cell* corredor = new Corridor(x,y);
    corredor->setVisited(cell->isVisited());
    corredor->top = cell->top;
    corredor->bottom = cell->bottom;
    corredor->left = cell->left;
    corredor->right = cell->right;

    map[x][y] = corredor;
}


vector<vector<Cell *> > Map::getWhitePositionCells(){
    vector<vector<Cell *> > visited;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j <= floor(width / 2.0); j += 2) {
            changeToCorridor(map[i][j]);
            aux.push_back(map[i][j]);
        }
        visited.push_back(aux);
    }

    return visited;
}


Cell* Map::randomCellPosition(vector<vector<Cell *> > visited){
    // Size Height and Width visited'list.
    int h = visited.size();
    int w = visited[0].size();

    int randX, randY;
    randX = rand()%(w+1);
    randY = rand()%(int)(floor((h+1)/2.0));

    int in = 0;
    for (int i = 0; i < visited.size(); i++){
        for (int j = 0; j < visited[0].size(); j++){
            if(!visited[i][j]->isVisited()){
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
    Cell *position = randomCellPosition(visited);
    position->setVisited(true); 
    int quantidadeVisitados = 1;

    stack<Cell*> stack;
    while(quantidadeVisitados < h*w)
    {
        //printV(visited);
        position = randomDiscoverPath(position);

        if(position == NULL){
            position = stack.top();
            stack.pop();
        }
        else if(!position->isVisited()){
            position->setVisited(true);
            stack.push(position);
            quantidadeVisitados++;
        }
    }
} // inside

bool Map::insideCondition(int x, int y){
    return (x >= 0 && x < (visited.size())) && (y >=0 && y < visited[0].size());
}



Cell* Map::randomDiscoverPath(Cell * c){
    int roll;

    vector<int> shuffle;
    Corridor *tempCell;
    int x,y;


    x = floor((c->getX()-1)/2.0);
    y = floor((c->getY()-1)/2.0);

    for(int i=1;i<=4;i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());


    for (int i = 0; i < shuffle.size(); i++)
    {
        if((shuffle[i] == UP) && (insideCondition(x-1, y))){
            x--;
            changeToCorridor(*c->top);
        } 
        else if((shuffle[i] == DOWN) && (insideCondition(x+1, y))){
            x++;
            changeToCorridor(*c->bottom);
        } 
        else if((shuffle[i] == LEFT) && (insideCondition(x, y-1))){
            y--;
            changeToCorridor(*c->left);
        }
        else if((shuffle[i] == RIGHT) && (insideCondition(x, y+1))){
            y++;
            changeToCorridor(*c->right);
        }
        return visited[x][y];
    }

    return NULL;
}


void Map::mirror(){
    for (int i = 0; i <= heigth - 1; i++){
        for (int j = floor(width / 2.0) - 1; j >= 0; j--){
            map[i][width-j-1] = map[i][j]; 
        }
    }
}

void Map::middle(){
    int mid = floor(width / 2.0);

    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            changeToCorridor(map[i][mid]);
    }
}
