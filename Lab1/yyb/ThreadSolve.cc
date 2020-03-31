#include <thread>
#include <mutex>
#include "ThreadSolve.h"
#include<iostream>
#include <semaphore.h>
#include<iostream>
using namespace std;
std::mutex mtx;
sem_t sem;
void ThreadSolve::Wk_Thread_Begin()
{
    while(working)
    {
        if(!puzzle_qe->empty())
        {
            // cout<<"正在处理队列："<<puzzle_qe->front()->count<<endl;
            mtx.lock(); 
                addThread(puzzle_qe->front());
                print_qe->push(puzzle_qe->front());
               // cout<<"队列头部正在处理的puzzle编号："<<puzzle_qe->front()->getNum()<<endl;
                if(puzzle_qe->front()->getNum()==MAX_INT)
                {   
                    mtx.unlock(); 
                    working=false;
                    return;
                }
                puzzle_qe->pop();
            mtx.unlock();
        }
    }
}

void ThreadSolve::addThread(Solve* sol)
{
    std::thread t1=sol->basicThread(0,sol->puzzle);
    t1.detach();
}

void ThreadSolve::add(Solve* sol)
{
        puzzle_qe->push(sol);
}


