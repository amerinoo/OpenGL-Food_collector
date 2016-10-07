#include <iostream>
#include "map.h"
using namespace std;

int main(){
	Map map (11,10);
	map.generate();
	map.print();
}
