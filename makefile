CXX=g++
LD=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

BLD=./build/
SRC=./src/

all: diff doc

diff: $(BLD)diff.o $(BLD)file.o $(BLD)folder.o $(BLD)io.o $(BLD)json.o $(BLD)main.o $(BLD)result.o $(BLD)exception.o
	$(LD) -o $@ $^

clean:
	rm -f diff $(BLD)*

compile: diff

run:
	./diff

doc: diff
	rm -rf ./doc/* && doxygen

$(BLD)%o: $(SRC)%cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BLD)diff.o: $(SRC)diff.cpp $(SRC)diff.hpp $(SRC)file.hpp $(SRC)io.hpp $(SRC)json.hpp $(SRC)result.hpp
$(BLD)file.o: $(SRC)file.cpp $(SRC)file.hpp $(SRC)io.hpp $(SRC)json.hpp
$(BLD)folder.o: $(SRC)folder.cpp $(SRC)folder.hpp $(SRC)diff.hpp $(SRC)file.hpp $(SRC)io.hpp $(SRC)json.hpp $(SRC)result.hpp
$(BLD)io.o: $(SRC)io.cpp $(SRC)io.hpp
$(BLD)json.o: $(SRC)json.cpp $(SRC)json.hpp $(SRC)exception.hpp
$(BLD)main.o: $(SRC)main.cpp $(SRC)diff.hpp $(SRC)file.hpp $(SRC)io.hpp $(SRC)json.hpp $(SRC)result.hpp $(SRC)folder.hpp
$(BLD)result.o: $(SRC)result.cpp $(SRC)result.hpp $(SRC)json.hpp
$(BLD)exception.o: $(SRC)exception.cpp $(SRC)exception.hpp