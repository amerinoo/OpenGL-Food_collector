#include <vector>
#include "map.h"
using namespace std;

#define blank -1
#define corridor 0
#define wall 1
#define init 2

Map::Map(int a, int b){
	width = a;
	heigth = b;
}

void Map::print(){
	for(int i=0;i<heigth;i++){
		for(int j=0;j<width;j++)
		{
			 cout << map[i][j];
		}
		cout << endl;
	}
}

void Map::generate(){
	outside();
	inside();
	mirror();
	middle();
}

void Map::outside(){
	for(int i=0; i<heigth; i++){
		vector<int> aux(width, init);
		for(int j=0; j<ceil(width/2.0); j++){
            if(i == 0 || i == heigth-1 || j == 0 || j == width-1 ){
                aux[j] = wall;
            }else
                aux[j] = blank;
		}
		map.push_back(aux);
    }
	map[1][1] = corridor;
}

void Map::inside(){
	srand(time(NULL));
	for(int i=1;i<heigth-1;i++){
		for(int j=1;j<floor(width/2.0);j++){
            int r = rand() % 2;

            if(r == 0)
                map[i][j] = corridor;
            else
                map[i][j] = wall;
		}
	}
}

void Map::mirror(){
	for(int i=0; i<=heigth-1; i++){
		for(int j=0; j<floor(width/2.0); j++){
			map[i][width-1-j] = map[i][j];
		}
	}
}

void Map::middle(){
	if (width%2 == 1) {
		for (int i = 1; i < heigth-1; i++) {
			map[i][floor(width/2.0)] = corridor;
		}
	}
}

bool Map::check(){
	return false;
}
