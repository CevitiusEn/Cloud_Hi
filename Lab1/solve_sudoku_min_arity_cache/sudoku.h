#ifndef SUDOKU_H
#define SUDOKU_H
#include "sudoku_min_arity_cache.h"
#include <mutex>
#include <semaphore.h>
/*extern int board[N];
extern int spaces[N];
extern int nspaces;
extern int (*chess)[COL];*/
extern std::mutex mtx;
extern sem_t sem;
extern int64_t start,end;
int64_t now();
void init_neighbors();
//void input(const char in[N]);
void init_cache();
/*
bool available(int guess, int cell);

bool solve_sudoku_basic(int which_space);
bool solve_sudoku_min_arity(int which_space);
bool solve_sudoku_min_arity_cache(int which_space);
bool solve_sudoku_dancing_links(int unused);*/
bool solved(Solve solve);
#endif

// #ifndef SUDOKU_H
// #define SUDOKU_H
// #include "sudoku_min_arity_cache.h"
// #include <mutex>
// #include <semaphore.h>


// extern int neighbors[N][NEIGHBOR];
// extern int board[N];
// extern int spaces[N];
// extern int nspaces;
// extern int (*chess)[COL];

// void init_neighbors();
// void input(const char in[N]);
// void init_cache();

// bool available(int guess, int cell);

// bool solve_sudoku_basic(int which_space);
// bool solve_sudoku_min_arity(int which_space);
// bool solve_sudoku_min_arity_cache(int which_space);
// bool solve_sudoku_dancing_links(int unused);
// bool solved();
// #endif
