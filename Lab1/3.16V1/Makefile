CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku_solve

sudoku_solve: Thread.cc neighbor.cc
	g++ -O2 -o $@ $^ -pthread
