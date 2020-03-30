#include <thread>
#include <mutex>
#include "ThreadSolve.h"
#include<iostream>
#include <semaphore.h>
using namespace std;
std::mutex mtx;
sem_t sem;
int64_t start;
void out_data(int* data)
{
    for(int i=0;i<81;i++)
        std::cout<<*(data+i);
    std::cout<<std::endl;
}

void outstd(std::queue<Solve*>* print_queue)
{
    Solve* tmp;
    while(1)
    {
        if(!print_queue->empty())
        {
            tmp=print_queue->front();
            if(tmp && tmp->isFinish())
            {
                if(tmp->getNum()==MAX_INT) 
                { 
                    int64_t end = now();
                    double sec = (end-start)/1000000.0;
                    return;
                } 
                 std::cout<<tmp->getNum()<<":"<<std::endl;
                out_data(tmp->getData());
                delete tmp;
                print_queue->pop(); 
            }
            else sem_wait(tmp->get_Sem());
        }
        
    }
}
void ThreadSolve::start()
{
     std::thread t(outstd,print_qe);  //开启输出线程
     t.detach();    //线程启动并且不堵塞
    while(work_flag)    //work_flag工作状态
    {
        if(!puzzle_qe->empty())    //存放 数独集 的工作队列不为空
        {
            sem_wait(&sem);
            mtx.lock(); //获得锁

                 addThread(puzzle_qe->front());  //处理队列最开始Data对象指针
                 print_qe->push(puzzle_qe->front());   //将队列最开始Data对象指针加入输出队列中

                 if(puzzle_qe->front()->getNum()==MAX_INT){mtx.unlock(); return;}
                 puzzle_qe->pop();//pop队列最开始Data对象指针

            mtx.unlock();
        }
    }
}

void ThreadSolve::append(Solve* sol)   //向工作队列添加一个Data对象指针
{
        puzzle_qe->push(sol);
}

void ThreadSolve::addThread(Solve* sol)    //添加一个 解数独 的线程
{
    std::thread t1=sol->basicThread(0,sol->puzzle);
    t1.detach();
}

void ThreadSolve::stop() //停止，将work_flag标置为0
{
    work_flag=false;
}

