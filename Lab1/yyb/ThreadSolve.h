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
        bool work_flag=true;


    public:
        ThreadSolve()
        {
            puzzle_qe = new std::queue<Solve*>;
            print_qe=new std::queue<Solve*>;
        };

        void start();

        void append(Solve*);

        void addThread(Solve*);

        void stop();


        std::queue<Solve*>* get_queue() {return puzzle_qe;};


       ~ThreadSolve()
       {
           delete puzzle_qe;
           delete print_qe;
       }
};

#endif