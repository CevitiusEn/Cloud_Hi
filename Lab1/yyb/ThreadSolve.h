#ifndef ThreadSolve_H
#define ThreadSolve_H
#include <iostream>
#include <queue>
#include "sudoku.h"
using namespace std;
struct ThreadSolve
{
    private:
        std::queue<Solve*>* puzzle_qe=nullptr;
        std::queue<Solve*>* print_qe=nullptr;
        bool working=true;

    public:
        ThreadSolve()
        {
            puzzle_qe = new std::queue<Solve*>;
            print_qe=new std::queue<Solve*>;
        };

        void Wk_Thread_Begin();

        void add(Solve*);

        void addThread(Solve*);

       ~ThreadSolve()
       {
           delete puzzle_qe;
           delete print_qe;
       }
};

#endif