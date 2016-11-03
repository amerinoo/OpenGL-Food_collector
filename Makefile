# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -lglut -lGLU -lGL -lm

# Files to compile
CFILES = main.cpp map.cpp cell.cpp wall.cpp corridor.cpp graphics.cpp

# The build target executable:
TARGET = food_collector

all: $(CFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
