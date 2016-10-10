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
            if(v[i][j]->type() == -1) cout << "_";
            else if(v[i][j]->type() ==  1) cout << "#";
            else cout << "·";

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
    inside();
    //mirror();
    //middle();
    print();
}

/*
 * Create and put all cells in the Vector<<Vector<Cell>>
 */
void Map::populationCells(){
    for (int i = 0; i < heigth; i++) {
        vector<Cell *> aux;
        for (int j = 0; j < ceil(width / 2.0); j++)
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
        c->top = map[c->getX()-1][c->getY()];
        //cout << "||| Entrei (1) |||";
    }
    //Bottom
    if((c->getX() + 1) <= heigth-1){
        c->bottom = map[c->getX()+1][c->getY()];
        //cout << "||| Entrei (2) |||";
    }
    //Left
    if((c->getY() - 1) >= 0){
        c->left = map[c->getX()][c->getY()-1];
        //cout << "||| Entrei (3) |||";
    }
    //Rigth
    if((c->getY() + 1) <= width+1){
        c->right = map[c->getX()][c->getY()+1];
        //cout << "||| Entrei (4) |||";
    }

    /*if(c->getX() == 1 && c->getY() == 1)
    {
        cout << "PQP ENtra " << c->top->getX() << " " << map[1][1]->top->getX() << " ." << endl;

        int j;
        cin >> j;
    }*/
    return c;
}



void Map::outside(){
    for (int i = 0; i < heigth; i++) {
        for (int j = 0; j < ceil(width / 2.0); j++)
        {
            Cell* parede = new Wall(map[i][j]->getX(), map[i][j]->getY());
            parede->setVisited(map[i][j]->isVisited());
            parede->top = map[i][j]->top;
            parede->bottom = map[i][j]->bottom;
            parede->left = map[i][j]->left;
            parede->right = map[i][j]->right;

            map[i][j] = parede;
        }
    }
    //map[1][1] = new Corridor(1, 1);
}



void Map::inside(){
    vector<vector<Cell *> > visited;

    //Add in Lista visited the Cells [Corridor]
    for (int i = 1; i < heigth - 1; i += 2) {
        vector<Cell *> aux;
        for (int j = 1; j <= floor(width / 2.0); j += 2) {
            Cell * auxCorridor = new Corridor(map[i][j]->getX(), map[i][j]->getY());
            auxCorridor->setVisited(false);
            auxCorridor->top = map[i][j]->top;
            auxCorridor->bottom = map[i][j]->bottom;
            auxCorridor->left = map[i][j]->left;
            auxCorridor->right = map[i][j]->right;

            map[i][j] = auxCorridor;
            aux.push_back(map[i][j]);
        }
        visited.push_back(aux);
    }

    // Size Height and Width visited'list.
    int h = visited.size();
    int w = visited[0].size();


    /*Cell * c;
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
    }*/

    srand(time(NULL));
    int rX, rY;

    rX = rand()%w;
    int rest = floor(h/2.0);
    rY = rand()%rest;

    int numVisited = 1;
    //stack<Cell *> path;
    Cell * cellPath;
    cellPath = visited[rX][rY];
    cellPath->setVisited(true);

    int j;
    
    connectCells();

    cout << "Passo 1: Verificação do Inicial -> " << rX << " " << rY << " " << endl;
    cout << "H: " << h << " W: "<< w << endl;
    while ((numVisited <= h * w) && !(cellPath == NULL)) {
        Cell *nextCell = randomDiscoverPath(cellPath);
        int sairLoop = 0;

        //cout << "Sai !" << endl;
        //cin >> j;

        if(nextCell == NULL){
            //cout << "Entao entrei aqui dentro desse if !" << endl;
            int auxX, auxY;
            for(int i=0;i<visited.size();i++){
                for(int j=0;j<visited[0].size();j++)
                {
                    if(!visited[i][j]->isVisited()){
                        cellPath = visited[i][j];
                        visited[i][j]->setVisited(true);
                        //numVisited++;
                        //cout << "Entreiiiiii no iffffff" << endl;
                        sairLoop=1;
                        break;
                    }
                }
                if(sairLoop==1)
                    break;
            }   
            /*if(sairLoop == 1)
            {
                cout << "Aconteceu algo." << endl;
                cout << "Posicao X: " << cellPath->getX() << " Y: " << cellPath->getY() << endl;
            }
            else
                cout << "Nada aconteceu." << endl;*/

            cellPath = nextCell;
        }else {
            cellPath = nextCell;
            cellPath->setVisited(true);
            numVisited++;
        }

        connectCells();
        print();
    }
} // inside

Cell* Map::randomDiscoverPath(Cell * c){
    int roll;

    vector<int> shuffle;
    Corridor *tempCell;

    for(int i=0;i<4;i++) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    for (int i = 0; i < shuffle.size(); i++)
    {
        cout << shuffle[i] << endl;

        if((shuffle[i] == 0) && (c->top != NULL) && (c->top->getX() > 0) && (c->top->type() == 1) && (!c->top->top->isVisited()))
        {
            //tempCell = (Corridor*)c->top;
            cout << "Escolheu lado cima." << endl;
            tempCell = new Corridor(c->top->getX(), c->top->getY());
            tempCell->setVisited(true);
            tempCell->top = c->top->top;
            tempCell->bottom = c->top->bottom;
            tempCell->left = c->top->left;
            tempCell->right = c->top->right;
            map[tempCell->getX()][tempCell->getY()] = tempCell;
            tempCell->top->setVisited(true);
            map[tempCell->getX()-1][tempCell->getY()] = tempCell->top;

            return tempCell->top;
        } 
        else if((shuffle[i] == 1) && (c->bottom != NULL) && (c->bottom->getX() < heigth-1) && (c->bottom->type() ==  1) && (!c->bottom->bottom->isVisited())){
            //tempCell = (Corridor*)c->bottom;
            cout << "Escolheu lado baixo" << endl;
            
            tempCell = new Corridor(c->bottom->getX(), c->bottom->getY());
            tempCell->setVisited(true);
            tempCell->top = c->bottom->top;
            tempCell->bottom = c->bottom->bottom;
            tempCell->left = c->bottom->left;
            tempCell->right = c->bottom->right;
            map[tempCell->getX()][tempCell->getY()] = tempCell;
            tempCell->bottom->setVisited(true);
            map[tempCell->getX()+1][tempCell->getY()] = tempCell->bottom;
            
            return tempCell->bottom;  
        } 
        else if((shuffle[i] == 2) && (c->left != NULL) && (c->left->getY() > 0) && (c->left->type() == 1) && (!c->left->left->isVisited())){
            //tempCell = (Corridor*)c->left;
            cout << "Escolheu lado esquerda" << endl;
            c->setVisited(true);
            tempCell = new Corridor(c->left->getX(), c->left->getY());
            tempCell->setVisited(true);
            tempCell->top = c->left->top;
            tempCell->bottom = c->left->bottom;
            tempCell->left = c->left->left;
            tempCell->right = c->left->right;
            map[tempCell->getX()][tempCell->getY()] = tempCell;
            tempCell->left->setVisited(true);
            map[tempCell->getX()][tempCell->getY()-1] = tempCell->left;

            return tempCell->left;
        }
        else if((shuffle[i] == 3) &&  (c->right != NULL) && (c->right->getY() < ceil(width/2.0)) && (c->right->type() == 1) && (!c->right->right->isVisited())){
            //tempCell = (Corridor*)c->right;
            cout << "Escolheu lado direita" << endl;
            c->setVisited(true);
            tempCell = new Corridor(c->right->getX(), c->right->getY());
            tempCell->setVisited(true);
            tempCell->top = c->right->top;
            tempCell->bottom = c->right->bottom;
            tempCell->left = c->right->left;
            tempCell->right = c->right->right;
            map[tempCell->getX()][tempCell->getY()] = tempCell;
            tempCell->right->setVisited(true);
            map[tempCell->getX()][tempCell->getY()+1] = tempCell->right;

            return tempCell->right;
        }
    }
    cout << "Vou retornar NULL " << endl;
    /*int l;
    cin >> l;*/
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

/*void Map::mirror(){
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
}*/

int Map::getRandomDirection(){
    return rand() % 4;
}
