CC=g++
FLAGS=-Wall -pedantic -g -O2

BLD=./build/
SRC=./src/

all: diff

diff: $(SRC)main.cpp $(BLD)bin_diff.o $(BLD)txt_diff.o $(BLD)jsn_diff.o
	$(CC) -std=c++11 $(FLAGS) -o diff $(SRC)main.cpp $(BLD)bin_diff.o $(BLD)txt_diff.o $(BLD)jsn_diff.o

$(BLD)bin_diff.o: $(SRC)bin_diff.cpp $(SRC)bin_diff.hpp 
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)bin_diff.o $(SRC)bin_diff.cpp

$(BLD)txt_diff.o: $(SRC)txt_diff.cpp $(SRC)txt_diff.hpp 
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)txt_diff.o $(SRC)txt_diff.cpp

$(BLD)jsn_diff.o: $(SRC)jsn_diff.cpp $(SRC)jsn_diff.hpp 
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)jsn_diff.o $(SRC)jsn_diff.cpp