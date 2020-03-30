#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "sudoku.h"
#include "ThreadSolve.h"


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
        solve->puzzle=puzzle;
        solve.input(puzzle);
        TSolve.append(solve);
        num++;
    }
}

  
// 	//cout<<puzzle<<' ';
// 	if(solve.solve_sudoku_basic(0,puzzle))
// 	{
// 	    if (!solved(solve))  assert(0);
// 	    cout<<"success"<<endl;
// 	}
// 	else
// 		cout<<"fail"<<endl;
// 	return true;
//     }
//     else
//     {
// 	// pthread_mutex_unlock(&c->lock);
// 	return false;
//     }
// }

// void* Deal(void* threadNum) 
// {
//     int i=0;
//     char puzzle[128];
//     bool roop=true;
//     while(roop)
//     {
// 	cout<<"thread "<<threadNum<<endl;
// 	roop=readPuzzle(p,puzzle,sizeof puzzle);
//     }
//     return (void*)i;
// }

int main()
{
    init_neighbors();
    printf("input thread num: \n");
    int n;
    cin>>n;
    pthread_t thread[n];
    int retval[n];
    
    char filename[30];
    printf("input test file:");
    cin>>filename;

    int64_t start = now();
    p=&gloCoun;
    init(p,filename);
    
    ThreadSolve* Tsolve=new ThreadSolve();
    std::thread load(readPuzzle,p,TSolve);
    load.detach();
    Tsolve->start;
    pthread_exit(NULL); 
    // for(int i=0;i<n;i++)
    // {
	// if(pthread_create(&thread[i], NULL, Deal,(void*)i)!=0)
	// {
	//     printf("线程%d创建失败\n",i);
	// }
    // }

    // for(int i=0;i<n;i++)
    // {
	// if(pthread_join(thread[i], (void**)&retval[i])!=0)
	// {
	//     printf("cannot join with thread%d\n",i);
	// }
    // }
    // int64_t end = now();
    // double sec = (end-start)/1000000.0;

    // printf("count is %d\n",p->value);
    // for(int i=0;i<n;i++)
    // {
	// printf("Thread%d return : %d\n",i,retval[i]);
    // }
    // cout<<"Process time:"<<sec<<endl;
    return 0;
}
