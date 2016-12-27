# Project name: Food collection
# Version 4
# Student : Albert Eduard Merino Pulido

# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
CFLAGS = -lglut -lGLU -lGL -lm -ljpeg -Wall

# Files to compile
CFILES = main.cpp graphics.cpp textureLoader.cpp arduinoSerial.cpp game.cpp \
			strategy.cpp expectimaxAgent.cpp reflexAgent.cpp agent.cpp map.cpp cell.cpp \
			particle.cpp enums.h drawer.cpp jsoncpp.cpp

# Files' headers
HFILES = graphics.h textureLoader.h arduinoSerial.h game.h strategy.h \
			expectimaxAgent.h reflexAgent.h agent.h map.h cell.h particle.h drawer.h

# The build target executable:
TARGET = food_collector

ALL : $(TARGET)

$(TARGET): $(CFILES) $(HFILES)
	$(CC) $(CFILES) -o $(TARGET) $(CFLAGS)

clean:
	$(RM) $(TARGET)
