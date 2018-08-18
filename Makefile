OBJ=./obj
BIN=./bin

$(shell mkdir -p $(OBJ))
$(shell mkdir -p $(BIN))

.PHONY: all

all: $(BIN)/8puzzle
$(BIN)/8puzzle:	$(OBJ)/8puzzle.o $(OBJ)/search.o
	g++ -o $(BIN)/8puzzle $(OBJ)/8puzzle.o $(OBJ)/search.o
$(OBJ)/8puzzle.o: 8puzzle.cpp search.h
	g++ -c 8puzzle.cpp -o $(OBJ)/8puzzle.o -std=c++11
$(OBJ)/search.o: search.cpp search.h
	g++ -c search.cpp -o $(OBJ)/search.o -std=c++11
