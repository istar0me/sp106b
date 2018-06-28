#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// 加入 mutex
pthread_mutex_t x;
pthread_mutex_t y;

void *A(); 
void *B(); 

int main(int argc, char *argv[])
{
    pthread_t threadA, threadB; // 宣告 pthread 變數 threadA 與 threadB
    pthread_attr_t attr; // 定義 pthread 的屬性

    pthread_attr_init(&attr); // 初始化 pthread 的屬性
    pthread_mutex_init(&x, NULL); // 初始化 mutex x
    pthread_mutex_init(&y, NULL); // 初始化 mutex y

    pthread_create(&threadA, NULL, A, NULL); // 新增一個名為執行函數 A 的執行緒 threadA，不帶參數與屬性
    pthread_create(&threadB, NULL, B, NULL); // 新增一個名為執行函數 B 的執行緒 threadB，不帶參數與屬性

    pthread_join(threadA, NULL); // 暫停當前的 threadA，直到另外一個執行緒結束
    pthread_join(threadB, NULL); // 暫停當前的 threadB，直到另外一個執行緒結束

    pthread_mutex_destroy(&x); // 移除 mutex x
    pthread_mutex_destroy(&y); // 移除 mutex y
}

void *A() 
{
    pthread_mutex_lock(&x); // 上鎖 mutex x
    printf("A lock x\n");
    sleep(1); // 暫停一秒，讓 OS 不耐煩，而去執行其他 thread(?)
    pthread_mutex_lock(&y);
    printf("A lock y\n");
    pthread_mutex_unlock(&y); 
    pthread_mutex_unlock(&x); 

    printf("finished A\n");

    pthread_exit(0);
}

void *B()
{
    
    pthread_mutex_lock(&y);
    printf("B lock y\n");
    sleep(1);
    pthread_mutex_lock(&x);
    printf("B lock x\n");
    pthread_mutex_unlock(&x);
    pthread_mutex_unlock(&y);

    pthread_exit(0);
}
