#include <bits/stdc++.h>
#include "map.h"
using namespace std;

Map::Map(int a, int b){
	width = a;
	heigth = b;
}
void Map::generate(){
	srand(time(NULL));
	int i, j;
    int matriz[10][10];

	// Ponendo los unos de las laterais e los zeros a dentro.
	for(i=0;i<width;i++){
		for(j=0;j<heigth;j++){
            if(i == 0 || i == width-1 || j == 0 || j == heigth-1 )
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
		}
    }

    cout << endl;

	for(i=1;i<width-1;i++)
	{
		for(j=1;j<floor(heigth/2);j++)
		{
            int r = rand() % 2;

            if(r == 0)
                matriz[i][j] = 0;
            else
                matriz[i][j] = 1;
		}
	}

    cout << endl;
}
void Map::print(){
	for(i=0;i<width;i++)
	{
		for(j=0;j<heigth;j++)
		{
             cout << matriz[i][j];
		}
		cout << endl;
    }

    for(i=0;i<=width-1;i++)
	{
		for(j=0;j<floor(heigth/2);j++)
		{
            matriz[i][width-1-j] = matriz[i][j];
		}
	}

    cout << endl;
    // Mostrar
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
             cout << matriz[i][j];
		}
		cout << endl;
    }
}


