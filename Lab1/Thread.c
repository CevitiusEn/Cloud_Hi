#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Counter_t
{
    int value;
    FILE* fp;
    pthread_mutex_t lock;
}Counter_t;
Counter_t gloCoun,*p;

void init(Counter_t *c,char* filename)
{
    c->value=0;
    c->fp = fopen(filename, "r");
    pthread_mutex_init(&c->lock,NULL);
}

bool readPuzzle(Counter_t *c,char *puzzle,int size)
{
    bool retBool;
    pthread_mutex_lock(&c->lock);
    if(fgets(puzzle,size,c->fp)!=NULL)
    {
	c->value++;
	retBool=true;
    }
    else
    {
	retBool=false;
    }
    pthread_mutex_unlock(&c->lock);
    return retBool;
}

void* Deal()
{
    int i=0;
    char puzzle[128];
    while(readPuzzle(p,puzzle,sizeof puzzle))
    {
	printf("%s\n",puzzle);
    }
    return (void*)(long)i;
}

int main()
{
    printf("input thread num: \n");
    int n;
    scanf("%d",&n);
    pthread_t thread[n];
    int retval[n],beginTime,endTime;
    
    char filename[30];
    printf("input test file:");
    scanf("%s",&filename);

    beginTime=clock();
    p=&gloCoun;
    init(p,filename);
    //judge if thread is successfully created
    if(ret_thrd1!=0){
	   printf("线程1创建失败\n");
    }
    else{
	   printf("线程1创建成功\n");
    }
    
    if(ret_thrd2!=0){
	   printf("线程2创建失败\n");
    }
    else{
	   printf("线程2创建成功\n");
    }

    pJoin_thrd1=pthread_join(thread1, (void**)&retval1);
    if (pJoin_thrd1 != 0) {
        printf("cannot join with thread1\n");
    }
    printf("Process time:%d\n",endTime-beginTime);
    return 0;
}
