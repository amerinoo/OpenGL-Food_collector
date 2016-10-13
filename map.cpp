#include "wall.h"
#include "corridor.h"
#include "map.h"
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
            /*if(v[i][j]->getType() == -1) cout << "_";
            else if(v[i][j]->getType() ==  1) cout << "#";
            else cout << "·";*/
            cout << v[i][j]->getSymbol();
            //cout << endl;
            //cout << v[i][j]->top->getX() << " " << v[i][j]->top->getY() << endl;
            //cout << v[i][j]->bottom->getX() << " " << v[i][j]->bottom->getY() << endl;
            //cout << v[i][j]->left->getX() << " " << v[i][j]->left->getY() << endl;
            //cout << v[i][j]->right->getX() << " " << v[i][j]->right->getY() << endl;
            //cout << endl;

        }
        cout << endl;
    }
    cout << endl;
}

void Map::generate(){
    srand(time(NULL));
    populationCells();
    connectCells();
    outside();

    /*cout << "Antes" << endl;
    cout << "X : " << (*map[1][1]->top)->getX() << " " << "Y : " << (*map[1][1]->top)->getY() << " ";
    cout << "Atual" << endl;
    cout << "X : " << map[1][1]->getX() << " " << "Y : " << map[1][1]->getY() << " ";*/

    inside();
    mirror();
    //middle();
    print();
}

/*
 * Create and put all cells in the Vector<<Vector<Cell>>
 */
void Map::populationCells(){
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < width; j++)
            aux.push_back(new Cell(i, j));
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

Wall* Map::copyToWall(Cell *cell)
{
    Cell* parede = new Wall(cell->getX(), cell->getY());
    parede->setVisited(cell->isVisited());
    parede->top = cell->top;
    parede->bottom = cell->bottom;
    parede->left = cell->left;
    parede->right = cell->right;

    return (Wall*)parede;
}

Corridor* Map::copyToCorridor(Cell *cell)
{
    Cell* corredor = new Corridor(cell->getX(), cell->getY());
    corredor->setVisited(cell->isVisited());
    corredor->top = cell->top;
    corredor->bottom = cell->bottom;
    corredor->left = cell->left;
    corredor->right = cell->right;

    return (Corridor*)corredor;
}

void Map::outside(){
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < ceil(width / 2.0); j++) {
            //cout << "Map[i][j] -> " << map[i][j]->getX() << " " << map[i][j]->getY() << " Parede->" << parede->getX() << " " << parede->getY() << endl;
            map[i][j] = copyToWall(map[i][j]);
        }
    }
}

void Map::putWhiteCells(){
    for (int i = 1; i < heigth - 1; i += 2) {
        for (int j = 1; j <= floor(width / 2.0); j += 2) {
            map[i][j] = copyToCorridor(map[i][j]);
        }
    }
}

vector<vector<Cell *> > Map::getWhitePositionCells(){
    vector<vector<Cell *> > visited;
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j <= floor(width / 2.0); j += 2) {
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
    srand (time(NULL));
    randX = rand()%(w+1);
    randY = rand()%(int)(floor((h+1)/2.0));

    int in = 0;
    for (int i = 0; i < visited.size(); i++){
        for (int j = 0; j < visited[0].size(); j++){
            //cout << "i:"<<i<<"j:"<<j<<endl;
            if(!visited[i][j]->isVisited()){
                //cout << "Mostrando final: " << visited[i][j]->isVisited() << "X : " << i << " y: "<< j << "Teste: " << visited[i][j]->getX() << endl;
                //visited[i][j]->setVisited(true);
                return visited[i][j];
            }
        }
    }
    return NULL;

    /*while(visited[randX][randY]->isVisited()){
        srand (time(NULL));
        randX = rand()%w;
        randY = rand()%(int)(floor(h/2.0));
        //cout << randX << " " << randY << endl;
    }*/
}

void Map::inside(){
    putWhiteCells();
    vector<vector<Cell *> > visited = getWhitePositionCells();

    /*for (int i = 0; i < visited.size(); i++){
        for (int j = 0; j < visited[0].size(); j++){
            cout << visited[i][j]->isVisited() << " ";
        }
        cout << endl;
    }*/

    int h = visited.size();
    int w = visited[0].size();


    // Primeiro elemento visitado.
    Cell *inicial = randomCellPosition(visited);
    inicial = map[inicial->getX()][inicial->getY()];
    inicial->setVisited(true);
    int quantidadeVisitados = 1;

    cout << " ...:: Inicio verificando ::..." << endl;
    cout << "Inicial : " << inicial->getX() << " " << inicial->getY() << "." << endl;
    while(inicial != NULL)// && (quantidadeVisitados <= (h*w)))
    {
        inicial = randomDiscoverPath(inicial);

        if(inicial == NULL){
            inicial = randomCellPosition(visited);
            if(inicial != NULL){
                inicial = map[inicial->getX()][inicial->getY()];
                inicial->setVisited(true);
                //cout << "Saiu aqui 2" << endl;
            }
        }
        else{
            //print();
        }
        quantidadeVisitados++;
    }
} // inside

bool Map::insideCondition(Cell *c){
    int x, y;
    x = c->getX();
    y = c->getY();

    if((x >= 1 && x < (heigth-1)) && (y >= 1 && y < (width-1)))
        return true;
    else
        return false;
}



Cell* Map::randomDiscoverPath(Cell * c){
    int roll;

    vector<int> shuffle;
    Corridor *tempCell;

    for(int i=0;i<4;i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    //cout << "Ordem shuffle: ";
    /*for (int i = 0; i < shuffle.size(); i++)
        cout << shuffle[i] << " ";
    cout << endl;*/

    for (int i = 0; i < shuffle.size(); i++)
    {
        //cout << shuffle[i] << endl;

        if((shuffle[i] == 0)){
            //cout << "Top 1" << endl;
            if(((*c->top) != NULL)){
                //cout << "Top 2" << endl;
                if(insideCondition((*c->top))){
                    //cout << "Top 3" << endl;
                    if(((*c->top)->getType() == 1)){
                        //cout << "Top 4" << endl;
                        //if((!(*(*c->top)->top)->isVisited())){
                            //cout << "Top 5" << endl;
                            //tempCell = (Corridor*)c->top;
                            //cout << "Escolheu lado cima." << endl;
                            tempCell = copyToCorridor(*c->top);

                            map[tempCell->getX()][tempCell->getY()] = tempCell;
                            (*tempCell->top)->setVisited(true);
                            map[tempCell->getX()-1][tempCell->getY()] = (*tempCell->top);

                            return (*tempCell->top);
                        //}
                    }
                }
            }
        } 
        else if((shuffle[i] == 1))
        {
            if(((*c->bottom) != NULL)){
                //cout << "Bottom 1" << endl;
                if(insideCondition((*c->bottom))){
                    //cout << "Bottom 2" << endl;
                    if((*c->bottom)->getX() < heigth-1){
                        //cout << "Bottom 3" << endl;
                        if((*c->bottom)->getType() ==  1){
                            //cout << "Bottom 4" << endl;
                            //if((!(*(*c->bottom)->bottom)->isVisited())){
                                //cout << "Bottom 5" << endl;
                                //tempCell = (Corridor*)c->bottom;
                                //cout << "Escolheu lado baixo" << endl;

                                tempCell = copyToCorridor(*c->bottom);

                                map[tempCell->getX()][tempCell->getY()] = tempCell;
                                (*tempCell->bottom)->setVisited(true);
                                map[tempCell->getX()+1][tempCell->getY()] = (*tempCell->bottom);
                                
                                return (*tempCell->bottom); 
                            //}
                        }
                    }
                }
            }
        } 
        else if((shuffle[i] == 2))
        {
            if(((*c->left) != NULL)){
                //cout << "Left 1" << endl;
                if(insideCondition((*c->left))){
                    //cout << "Left 2" << endl;
                    if((*c->left)->getY() > 0){
                        //cout << "Left 3" << endl;
                        if((*c->left)->getType() == 1){
                            //cout << "Left 4" << endl;
                            //if(!(*(*c->left)->left)->isVisited()){
                                //cout << "Left 5" << endl;
                                //tempCell = (Corridor*)c->left;
                                //cout << "Escolheu lado esquerda" << endl;
                                c->setVisited(true);
                                
                                tempCell = copyToCorridor(*c->left);

                                map[tempCell->getX()][tempCell->getY()] = tempCell;
                                (*tempCell->left)->setVisited(true);
                                map[tempCell->getX()][tempCell->getY()-1] = (*tempCell->left);

                                return (*tempCell->left);
                            //}
                        } 
                    } 
                }
            }
        }
        else if((shuffle[i] == 3)){
            if(((*c->right) != NULL)){
                //cout << "Right 1" << endl;
                if(insideCondition((*c->right))){
                    //cout << "Right 2" << endl;
                    if(((*c->right)->getY() < ceil(width/2.0))){
                        //cout << "Right 3" << endl;
                        if(((*c->right)->getType() == 1)){
                            //cout << "Right 4" << endl;
                            //if((!(*(*c->right)->right)->isVisited())){
                                //cout << "Right 5" << endl;
                                //tempCell = (Corridor*)c->right;
                                //cout << "Escolheu lado direita" << endl;
                                c->setVisited(true);

                                tempCell = copyToCorridor(*c->right);

                                map[tempCell->getX()][tempCell->getY()] = tempCell;
                                (*tempCell->right)->setVisited(true);
                                map[tempCell->getX()][tempCell->getY()+1] = (*tempCell->right);

                                return (*tempCell->right);
                            //}
                        }
                    }
                }
            }
        }
    }
    //cout << "Vou retornar NULL " << endl;

    return NULL;
}

bool Map::hasValidNeighbours(Cell * c){
    /*vector<Cell *> neighbours = c->getNeighbours();
    std::cout << neighbours.size() << std::endl;
    for (int i = 0; i < neighbours.size(); i++) {
        std::cout << neighbours[i]->isVisited() << std::endl;
        if (!neighbours[i]->isVisited()) {
            return true;
        }
    }*/
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
    cout << "mirror" << endl;

    for (int i = 0; i <= heigth - 1; i++){
        for (int j = floor(width / 2.0) - 1; j >= 0; j--)
        {
            /*cout << map[i][j]->isVisited() << " ";
            cout << i << " " << width-j << "<-" << i << " " << j << endl;*/
            map[i][width-j-1] = map[i][j]; 
            //map[i].push_back();
        }
        //cout << endl;
    }
}

/*void Map::middle(){
    int mid = floor(width / 2.0);

    if (width % 2 == 1) {
        for (int i = 1; i < heigth - 1; i++)
            map[i][mid] = new Corridor(i, mid);
    }
}*/

int Map::getRandomDirection(){
    return rand() % 4;
}
