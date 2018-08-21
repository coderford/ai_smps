OBJ=./obj
BIN=./bin

$(shell mkdir -p $(OBJ))
$(shell mkdir -p $(BIN))

.PHONY: all

all: $(BIN)/8puzzle $(BIN)/waterjug
$(BIN)/8puzzle: $(OBJ)/8puzzle.o $(OBJ)/search.o
	g++ -o $(BIN)/8puzzle $(OBJ)/8puzzle.o $(OBJ)/search.o
$(OBJ)/8puzzle.o: src/8puzzle.cpp include/search.h
	g++ -c src/8puzzle.cpp -o $(OBJ)/8puzzle.o -std=c++11 -I include
$(OBJ)/search.o: src/search.cpp include/search.h
	g++ -c src/search.cpp -o $(OBJ)/search.o -std=c++11 -I include

$(BIN)/waterjug: $(OBJ)/waterjug.o $(OBJ)/search.o
	g++ -o $(BIN)/waterjug $(OBJ)/waterjug.o $(OBJ)/search.o
$(OBJ)/waterjug.o: src/waterjug.cpp include/search.h
	g++ -c src/waterjug.cpp -o $(OBJ)/waterjug.o -std=c++11 -I include
