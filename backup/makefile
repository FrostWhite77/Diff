CC=g++
FLAGS=-Wall -pedantic -g -O2

BLD=./build/
SRC=./src/

all: diff

diff: $(SRC)main.cpp $(BLD)diff.o $(BLD)folder.o $(BLD)result.o $(BLD)io.o
	$(CC) -std=c++11 $(FLAGS) -o diff $(SRC)main.cpp $(BLD)diff.o $(BLD)file.o $(BLD)folder.o $(BLD)result.o $(BLD)settings.o $(BLD)io.o $(BLD)json.o

$(BLD)folder.o: $(SRC)folder.cpp $(SRC)folder.hpp $(BLD)diff.o $(BLD)result.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)folder.o $(SRC)folder.cpp

$(BLD)diff.o: $(SRC)diff.cpp $(SRC)diff.hpp $(BLD)file.o $(BLD)result.o $(BLD)settings.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)diff.o $(SRC)diff.cpp

$(BLD)file.o: $(SRC)file.cpp $(SRC)file.hpp $(BLD)json.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)file.o $(SRC)file.cpp

$(BLD)result.o: $(SRC)result.cpp $(SRC)result.hpp $(BLD)json.o
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)result.o $(SRC)result.cpp

$(BLD)json.o: $(SRC)json.cpp $(SRC)json.hpp
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)json.o $(SRC)json.cpp

$(BLD)settings.o: $(SRC)settings.cpp $(SRC)settings.hpp 
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)settings.o $(SRC)settings.cpp

$(BLD)io.o: $(SRC)io.cpp $(SRC)io.hpp 
	$(CC) -std=c++11 $(FLAGS) -c -o $(BLD)io.o $(SRC)io.cpp

clean:
	rm -rf $(BLD)*.o 
