#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "sudoku.h"
#include "ThreadSolve.h"
#include <cstring>
#include <thread>
#include <mutex>
#include <semaphore.h>
int64_t start,ending;
typedef struct Counter_t
{
    int value;
    FILE* fp;
    pthread_mutex_t lock;
}Counter_t;
Counter_t gloCoun,*p;

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

void init(Counter_t *c,char* filename)
{
    c->value=0;
    c->fp = fopen(filename, "r");
    pthread_mutex_init(&c->lock,NULL);
}

bool readPuzzle(Counter_t *c,ThreadSolve* TSolve)
{
    char puzzle[128];
    bool retBool;
    int num=1;
    // pthread_mutex_lock(&c->lock);
    while(fgets(puzzle,128,c->fp)!=NULL)
    {
        // pthread_mutex_unlock(&c->lock);
        Solve* solve=new Solve();
        solve->count=num;
        cout<<"loading.....num: "<<num;
        strcpy(solve->puzzle,puzzle);
        cout<<"    puzzle:  "<<solve->puzzle<<endl;
        TSolve->append(solve);
        num++;
    }
    Solve* solveEnd=new Solve();
    solveEnd->count=MAX_INT;
    TSolve->append(solveEnd);
}

int main()
{
    init_neighbors();
    char filename[30];
    printf("input test file:");
    cin>>filename;
    p=&gloCoun;
    init(p,filename);
    ThreadSolve* TSolve=new ThreadSolve();
    
    std::thread load(readPuzzle,p,TSolve);
    load.detach();
    start = now();
    TSolve->start();
    ending = now();
    double sec = (ending-start)/1000000.0;
    cout<<"用时："<<sec<<endl;
    pthread_exit(NULL); 
    return 0;
}
