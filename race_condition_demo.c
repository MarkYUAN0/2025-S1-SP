#include <pthread.h>
#include <stdio.h>

#define INCREMENTS 100000
long long counter = 0;             /* 全局共享变量 */

void *worker(void *arg)
{
    for (int i = 0; i < INCREMENTS; ++i)
        counter++;                 /* 读-改-写序列不是原子操作 → 竞态 */
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter = %lld (expect %d)\n",
           counter, 2 * INCREMENTS);
}

gcc -O2 race_condition_demo.c -pthread -o race_demo
for i in {1..5}; do ./race_demo; done
