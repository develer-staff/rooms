CC=g++
CFLAGS=-Wall
LDFLAGS=
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rooms.exe

all: compile install test

compile:
	$(CC) $(CFLAGS) -c src/*.cpp
	mv *.o build/

install:
	$(CC) build/*.o $(LDFLAGS) -o dist/rooms.exe

clean:
	rm -f -R dist/*
	rm -f -R build/*

test:
	./dist/rooms.exe
