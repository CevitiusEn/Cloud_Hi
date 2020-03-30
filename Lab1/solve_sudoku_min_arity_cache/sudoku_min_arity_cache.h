#include <thread>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <semaphore.h>
#include <strings.h>
using namespace std;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 ,MAX_INT=0x7fffffff};
const bool DEBUG_MODE = false;

const int NUM = 9;
class Solve
{
    public:
      bool occupied[N][NUM+1];
      int arity[N];
      bool finish=false;
      sem_t sem;
      int count;
      int (*chess)[COL];
      char puzzle[128];
      int neighbors[N][NEIGHBOR];
      int board[N];
      int spaces[N];
      int nspaces;
  Solve()
  {
      sem_init(&this->sem,0,0);
  }
  int getNum(){return count;}

  bool isFinish(){return finish;}

  sem_t* get_Sem(){return &sem;}

  int* getData(){return board;}
  void find_min_arity(int space)
  {
    int cell = spaces[space];
    int min_space = space;
    int min_arity = arity[cell];

    for (int sp = space+1; sp < nspaces && min_arity > 1; ++sp) {
      int cur_arity = arity[spaces[sp]];
      if (cur_arity < min_arity) {
        min_arity = cur_arity;
        min_space = sp;
      }
    }

    if (space != min_space) {
      std::swap(spaces[min_space], spaces[space]);
    }
  }

  void init_cache()
  {
    bzero(occupied, sizeof(occupied));
    std::fill(arity, arity + N, NUM);
    for (int cell = 0; cell < N; ++cell) {
      occupied[cell][0] = true;
      int val = board[cell];
      if (val > 0) {
        occupied[cell][val] = true;
        for (int n = 0; n < NEIGHBOR; ++n) {
          int neighbor = neighbors[cell][n];
          if (!occupied[neighbor][val]) {
            occupied[neighbor][val] = true;
            --arity[neighbor];
          }
        }
      }
    }
  }

  bool solve_sudoku_min_arity_cache(int which_space)
  {
    if (which_space >= nspaces) {
      return true;
    }

    find_min_arity(which_space);
    int cell = spaces[which_space];

    for (int guess = 1; guess <= NUM; ++guess) {
      if (!occupied[cell][guess]) {
        // hold
        assert(board[cell] == 0);
        board[cell] = guess;
        occupied[cell][guess] = true;

        // remember changes
        int modified[NEIGHBOR];
        int nmodified = 0;
        for (int n = 0; n < NEIGHBOR; ++n) {
          int neighbor = neighbors[cell][n];
          if (!occupied[neighbor][guess]) {
            occupied[neighbor][guess] = true;
            --arity[neighbor];
            modified[nmodified++] = neighbor;
          }
        }

        // try
        if (solve_sudoku_min_arity_cache(which_space+1)) {
          return true;
        }

        // unhold
        occupied[cell][guess] = false;
        assert(board[cell] == guess);
        board[cell] = 0;

        // undo changes
        for (int i = 0; i < nmodified; ++i) {
          int neighbor = modified[i];
          assert(occupied[neighbor][guess]);
          occupied[neighbor][guess] = false;
          ++arity[neighbor];
        }
      }
    }
    return false;
  }
  std::thread Thread_min_arity_cache(int which_space) 
  {
      return std::thread(&Solve::solve_sudoku_min_arity_cache, this, which_space);
  }
};