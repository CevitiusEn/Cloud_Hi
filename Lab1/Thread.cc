#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <list>
#include "sudoku.h"

char answer[10000][128];
typedef struct Counter_t
{
    int value,size;
    list<char *> sudoku;
    pthread_mutex_t lock;
}Counter_t;
Counter_t gloCoun,*p;

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

void init(Counter_t *c)
{
    c->value=0;
    pthread_mutex_init(&c->lock,NULL);
}

bool readPuzzle(Counter_t *c)
{
    int position=0;
    bool retBool;
    Solve solve;
    pthread_mutex_lock(&c->lock);
    if(c->sudoku.size()!=0)
    {
	char puzzle[128];
	position=c->value;
	c->value++;
	strcpy(puzzle,*(c->sudoku.begin()));
	c->sudoku.pop_front();
	pthread_mutex_unlock(&c->lock);
	usleep(10);

	solve.input(puzzle);
	if(solve.solve_sudoku_basic(0,puzzle))
	{
	    if (!solved(solve)) assert(0);
	    pthread_mutex_lock(&c->lock);
	    strcpy(answer[position],puzzle);
	    pthread_mutex_unlock(&c->lock);
	    usleep(10);
	    if(output) cout<<"success"<<endl;
	}
	else
	{
	    pthread_mutex_lock(&c->lock);
	    strcpy(answer[position],"fail");
	    pthread_mutex_unlock(&c->lock);
	    if(output) cout<<"fail"<<endl;
	}
	return true;
    }
    else
    {
	pthread_mutex_unlock(&c->lock);
	return false;
    }
}

void* Deal(void* threadNum) 
{
    int i=0;
    bool roop=true;
    while(roop)
    {
	if(output) cout<<"thread "<<threadNum<<endl;
	roop=readPuzzle(p);
    }
    return (void*)i;
}

int main()
{
    FILE* fp;
    init_neighbors();
    int n=sysconf(_SC_NPROCESSORS_CONF);

    pthread_t thread[n];
    int retval[n];
    
    char filename[30];
    cin>>filename;
    fp=fopen(filename, "r");

    int64_t start = now();
    p=&gloCoun;
    init(p);
    while(true)
    {	
	char *puzzle=new char[128];
	if(fgets(puzzle,128,fp)==NULL) break;
	p->sudoku.push_back(puzzle);
    }
    p->size=p->sudoku.size();    

    for(int i=0;i<n;i++)
    {
	if(pthread_create(&thread[i], NULL, Deal,(void*)i)!=0)
	{
	    //printf("线程%d创建失败\n",i);
	}
    }

    for(int i=0;i<n;i++)
    {
	if(pthread_join(thread[i], (void**)&retval[i])!=0)
	{
	    //printf("cannot join with thread%d\n",i);
	}
    }
    int64_t end = now();
    double sec = (end-start)/1000000.0;

    //printf("count is %d\n",p->value);
    /*for(int i=0;i<n;i++)
    {
	printf("Thread%d return : %d\n",i,retval[i]);
    }*/
    
    for(int i=0;i<p->size;i++)
    {
	cout<<answer[i]<<endl;
    }

    for(int i=0;p->sudoku.size()>0;i++)
    {
	*(p->sudoku.begin())=NULL;
	p->sudoku.pop_front();
    }
    //cout<<"Process time:"<<sec<<endl;
    return 0;
}
