#include <vector>
#include "map.h"
using namespace std;

Map::Map(int a, int b){
	width = a;
	heigth = b;
}
void Map::generate(){
	int init = -1;
	int corridor = 0;
	int wall = 1;
	int mirror = 2;

	srand(time(NULL));
	int i, j;
	// Outside
	for(i=0; i<heigth; i++){
		vector<int> aux(width, mirror);
		for(j=0; j<ceil(width/2.0); j++){
            if(i == 0 || i == heigth-1 || j == 0 || j == width-1 ){
                aux[j] = wall;
            }else
                aux[j] = init;
		}
		map.push_back(aux);
    }
	map[1][1] = corridor;

	//Inside
	for(i=1;i<heigth-1;i++)
	{
		for(j=1;j<floor(width/2.0);j++)
		{
            int r = rand() % 2;

            if(r == 0)
                map[i][j] = corridor;
            else
                map[i][j] = wall;
		}
	}

	//Mirror
	for(i=0; i<=heigth-1; i++){
		for(j=0; j<floor(width/2.0); j++){
			map[i][width-1-j] = map[i][j];
		}
	}
	//Corredor in the middle
	if (width%2 == 1) {
		for (i = 1; i < heigth-1; i++) {
			map[i][floor(width/2.0)] = corridor;
		}
	}

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
