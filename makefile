CC=g++
FLAGS=-Wall -pedantic -g -O2

BLD=./build/
SRC=./src/

all: diff

diff: $(SRC)main.cpp $(BLD)diff.o $(SRC)tests.cpp
	$(CC) -std=c++11 $(FLAGS) -o diff $(SRC)main.cpp $(BLD)diff.o $(BLD)file.o $(BLD)result.o

$(BLD)diff.o: $(SRC)diff.cpp $(SRC)diff.hpp $(BLD)file.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)diff.o $(SRC)diff.cpp

$(BLD)file.o: $(SRC)file.cpp $(SRC)file.hpp $(BLD)result.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)file.o $(SRC)file.cpp

$(BLD)result.o: $(SRC)result.cpp $(SRC)result.hpp
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)result.o $(SRC)result.cpp