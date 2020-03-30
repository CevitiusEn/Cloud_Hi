CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku

sudoku: Thread.cc neighbor.cc ThreadSolve.cc
	g++ -O2 -o $@ $^ -std=c++11 -pthread 

# sudoku: Thread.o neighbor.o ThreadSolve.o
# 	g++ Thread.o neighbor.o ThreadSolve.o -std=c++11 -pthread
# Thread.o:Thread.cc ThreadSolve.h 
# 	g++ -c Thread.cc -std=c++11 -pthread
# neighbor.o:neighbor.cc sudoku.h
# 	g++ -c neighbor.cc -std=c++11 -pthread
# ThreadSolve.o:ThreadSolve.cc ThreadSolve.h
# 	g++ -c ThreadSolve.cc -std=c++11 -pthread

clean:
	rm Thread.o
	rm neighbor.o
	rm ThreadSolve.o