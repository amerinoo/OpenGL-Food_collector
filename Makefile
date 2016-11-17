# Project name: Food collection
# Version 2
# Student 1: Albert Eduard Merino Pulido
# Student 2: Tan Kin Tat

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -lglut -lGLU -lGL -lm -Wall

# Files to compile
CFILES = main.cpp graphics.cpp game.cpp strategy.cpp reflexAgent.cpp agent.cpp map.cpp cell.cpp particle.cpp enums.h drawer.cpp

# Files' headers
HFILES = graphics.h game.h strategy.h reflexAgent.h agent.h map.h cell.h particle.h drawer.h

# The build target executable:
TARGET = food_collector

ALL : $(TARGET)

$(TARGET): $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
