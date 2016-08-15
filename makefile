CC=g++
LDFLAGS= -lglut -lGL -lGLU -lX11 -lm -lSOIL
CFLAGS= -c -g -Wall
SOURCES= main.cpp planet.cpp orbit.cpp rings.cpp camera.cpp
HEADERS= $(SOURCES:.cpp=.hpp)
OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE= solarsystem

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $< -o $@  $(CFLAGS)

test: all
	./$(EXECUTABLE)

.PHONY: clean
clean:
	rm $(OBJECTS) $(EXECUTABLE) *.zip
