pacman: main.cpp map.cpp cell.cpp wall.cpp corridor.cpp graphics.cpp
	g++ main.cpp map.cpp cell.cpp wall.cpp corridor.cpp graphics.cpp -o pacman -lglut -lGLU -lGL -lm
clean:
	rm pacman
