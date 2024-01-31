#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// ����ı���
int sharedVariable = 0;

// �����������ڱ����������
//PTHREAD_MUTEX_INITIALIZER��һ���꣬���ھ�̬��ʼ����������Ĭ��ֵ,���Ὣ����������Ϊ����״̬ 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// �߳�1�ĺ���
void *thread1Function(void *arg) {
    for (int i = 0; i < 5; ++i) {
        // ����
        pthread_mutex_lock(&mutex);

        // �޸Ĺ������
        sharedVariable++;
        printf("Thread 1: Incremented sharedVariable to %d\n", sharedVariable);

        // ����
        pthread_mutex_unlock(&mutex);

        // �߳�����һ��ʱ�䣬ģ����������
        sleep(1);
    }

    pthread_exit(NULL);
}

// �߳�2�ĺ���
void *thread2Function(void *arg) {
    for (int i = 0; i < 5; ++i) {
        // ����
        pthread_mutex_lock(&mutex);

        // ��ȡ���޸Ĺ������
        int currentValue = sharedVariable;
        printf("Thread 2: Got sharedVariable value: %d\n", currentValue);
        sharedVariable = currentValue * 2;
        printf("Thread 2: Doubled sharedVariable to %d\n", sharedVariable);

        // ����
        pthread_mutex_unlock(&mutex);

        // �߳�����һ��ʱ�䣬ģ����������
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    // �����߳�
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1Function, NULL);
    pthread_create(&thread2, NULL, thread2Function, NULL);

    // �ȴ��߳̽���
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // ���ٻ�����
    pthread_mutex_destroy(&mutex);

    return 0;
}

