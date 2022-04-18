#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h> Linux
#include <Windows.h>
#include <pthread.h>

void *myThreadFun(void *vargp)
{
    Sleep(1);
    printf("printing something from Thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id; //an integer used to identify the thread in the system
    printf("Before Thread\n");
    //pthread_create() to create a thread
    // 1 a pointer to thread_id
    // 2 指定属性 NULL使用默认属性
    // 3 创建的线程执行的函数名
    // 4 用于向函数myThreadFun传递参数
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
    /* 
    when you use windows, follw the command
    > gcc multiThread.c -lphread
    > a.exe
    Before Thread
    printing something from Thread
    After Thread
     */
}