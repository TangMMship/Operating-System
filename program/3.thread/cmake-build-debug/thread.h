#ifndef THREAD_H_
#define THREAD_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdatomic.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREAD 64
enum { T_FREE = 0, T_LIVE, T_DEAD, };

struct thread {
    int id, status;
    pthread_t thread;
    void (*entry)(int);     //指针函数，传入参数int型  作为后续要传入的函数fn，传入参数是id号
};

//申请线程池大小，初始地址给tptr
struct thread tpool[NTHREAD], *tptr = tpool;


//对于pthread_create传参
//传递参数的时候传地址： pthread_create(&ntid, NULL, thr_fn, &param1);
//线程函数的第一句通常是获取传入参数：Param tmp = *(Param *)arg;
//所以线程函数的传入参数*arg就是pthread_create(&ntid, NULL, thr_fn, &param1);的param1
//所以wrapper获取到tptr的地址 thread的线程函数是entry 在此执行
void *wrapper(void *arg) {
    struct thread *thread = (struct thread *)arg;
    thread->entry(thread->id);
    return NULL;
}

void create(void *fn) {
    assert(tptr - tpool < NTHREAD); //tptr是从tpool开始的，若小于就报错
    *tptr = (struct thread) {
            .id = tptr - tpool + 1,         //id号从1开始，每创建一个线程加1
            .status = T_LIVE,
            .entry = fn,
    };
    pthread_create(&(tptr->thread), NULL, wrapper, tptr);
    ++tptr;     //线程地址+1
}

void join() {
    //遍历线程池，若线程存活，等待线程结束
    for (int i = 0; i < NTHREAD; i++) {
        struct thread *t = &tpool[i];
        if (t->status == T_LIVE) {
            pthread_join(t->thread, NULL);
            t->status = T_DEAD;
        }
    }
}

__attribute__((destructor)) void cleanup() {
    join();
}
#endif
