#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 共享的变量
int sharedVariable = 0;

// 互斥锁，用于保护共享变量
//PTHREAD_MUTEX_INITIALIZER是一个宏，用于静态初始化互斥锁的默认值,它会将互斥锁设置为可用状态 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 线程1的函数
void *thread1Function(void *arg) {
    for (int i = 0; i < 5; ++i) {
        // 加锁
        pthread_mutex_lock(&mutex);

        // 修改共享变量
        sharedVariable++;
        printf("Thread 1: Incremented sharedVariable to %d\n", sharedVariable);

        // 解锁
        pthread_mutex_unlock(&mutex);

        // 线程休眠一段时间，模拟其他操作
        sleep(1);
    }

    pthread_exit(NULL);
}

// 线程2的函数
void *thread2Function(void *arg) {
    for (int i = 0; i < 5; ++i) {
        // 加锁
        pthread_mutex_lock(&mutex);

        // 获取并修改共享变量
        int currentValue = sharedVariable;
        printf("Thread 2: Got sharedVariable value: %d\n", currentValue);
        sharedVariable = currentValue * 2;
        printf("Thread 2: Doubled sharedVariable to %d\n", sharedVariable);

        // 解锁
        pthread_mutex_unlock(&mutex);

        // 线程休眠一段时间，模拟其他操作
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    // 创建线程
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1Function, NULL);
    pthread_create(&thread2, NULL, thread2Function, NULL);

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}

