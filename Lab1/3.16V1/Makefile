CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku

sudoku: Thread.cc neighbor.cc
	g++ -O2 -o $@ $^ -pthread
