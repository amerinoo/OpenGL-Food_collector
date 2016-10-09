pacman: main.cpp map.cpp cell.cpp wall.cpp corridor.cpp
	g++ main.cpp map.cpp cell.cpp wall.cpp corridor.cpp -o pacman
clean:
	rm pacman
