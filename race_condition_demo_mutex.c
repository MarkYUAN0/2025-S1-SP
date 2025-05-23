#include <pthread.h>
#include <stdio.h>

#define INCREMENTS 100000
long long counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;   /* 初始化互斥锁 */

void *worker(void *arg)
{
    for (int i = 0; i < INCREMENTS; ++i) {
        pthread_mutex_lock(&lock);      /* 进入临界区 :contentReference[oaicite:9]{index=9} */
        counter++;
        pthread_mutex_unlock(&lock);    /* 离开临界区 */
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter (mutex) = %lld\n", counter);
    pthread_mutex_destroy(&lock);
}

gcc -O2 race_condition_demo_mutex.c -pthread -o race_demo_mutex
./race_demo_mutex
