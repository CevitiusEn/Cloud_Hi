#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;

const bool DEBUG_MODE = false;
const bool output = false;
enum { ROW=9, COL=9, N = 81, NEIGHBOR = 20 };
const int NUM = 9;

extern int neighbors[N][NEIGHBOR];
class Solve{
public:
    int board[N];
    int spaces[N];
    int nspaces;
    int (*chess)[COL];
Solve()
{
    chess = (int (*)[COL])board;
}

void find_spaces()
{
  nspaces = 0;
  for (int cell = 0; cell < N; ++cell) {
    if (board[cell] == 0)
      spaces[nspaces++] = cell;
  }
}

void input(const char in[N])
{
  for (int cell = 0; cell < N; ++cell) {
    board[cell] = in[cell] - '0';
    assert(0 <= board[cell] && board[cell] <= NUM);
  }
  find_spaces();
}

bool available(int guess, int cell)
{
  for (int i = 0; i < NEIGHBOR; ++i) {
    int neighbor = neighbors[cell][i];
    if (board[neighbor] == guess) {
      return false;
    }
  }
  return true;
}

bool solve_sudoku_basic(int which_space,char* puzzle)
{
  if (which_space >= nspaces) {
    return true;
  }

  // find_min_arity(which_space);
  int cell = spaces[which_space];

  for (int guess = 1; guess <= NUM; ++guess) {
    if (available(guess, cell)) {
      // hold
      assert(board[cell] == 0);
      board[cell] = guess;
      puzzle[cell]=guess+'0';
      // try
      if (solve_sudoku_basic(which_space+1,puzzle)) {
        return true;
      }

      // unhold
      assert(board[cell] == guess);
      board[cell] = 0;
    }
  }
  return false;
}
};




