# Project name: Food collection
# Version 2
# Student 1: Albert Eduard Merino Pulido
# Student 2: Tan Kin Tat

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -lglut -lGLU -lGL -lm -Wall

# Files to compile
CFILES = main.cpp graphics.cpp colour.cpp game.cpp map.cpp cell.cpp wall.cpp corridor.cpp agent.cpp player.cpp enemy.cpp

# Files' headers
HFILES = graphics.h colour.h game.h map.h cell.h wall.h corridor.h agent.h player.h enemy.h

# The build target executable:
TARGET = food_collector

all: $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
