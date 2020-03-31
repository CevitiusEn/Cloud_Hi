#include <thread>
#include <mutex>
#include "ThreadSolve.h"
#include<iostream>
#include <semaphore.h>
using namespace std;
std::mutex mtx;
sem_t sem;
void ThreadSolve::start()
{

    while(work_flag) 
    {
        if(!puzzle_qe->empty())  
        {
            mtx.lock(); 

                addThread(puzzle_qe->front()); 
                cout<<"队列头部正在处理的puzzle编号："<<puzzle_qe->front()->getNum()<<endl;
                if(puzzle_qe->front()->getNum()==MAX_INT){mtx.unlock(); return;}
                puzzle_qe->pop();

            mtx.unlock();
        }
    }
}

void ThreadSolve::append(Solve* sol) 
{
        puzzle_qe->push(sol);
}

void ThreadSolve::addThread(Solve* sol) 
{
    std::thread t1=sol->Thread_min_arity_cache(0);
    t1.detach();
}


