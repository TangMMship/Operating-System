#include <stdio.h>
#include "thread.h"
#include "cmake-build-debug/thread.h"


int nums[]={2,5,44,9,7,46,3,22};
int sortnum[8];
int i=0;


void sleepsort_fn(int fn);
void sleep_sort(int numc);



int main() {
    //时间复杂度最低的sleep_sort  验证全局变量在线程中共享
    sleep_sort(8);

    for(int i=0;i<8;i++)
    {
        printf("nums[%d]=%d\n",i,sortnum[i]);
    }

    return 0;
}




void sleep_sort(int numc)
{
    for(int i=0;i<numc;i++)
    {
        create(&sleepsort_fn);
    }
    join();
}

void sleepsort_fn(int fn)
{
    int num;
    num=nums[fn-1];
    usleep(num*10000);
    sortnum[i]=num;i++;
    //printf("fd=%d,num=%d\n",fn,num);
    return;
}