#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *say_hello(void *arg)
{
    /* 线程编号既可由创建者传入，也可用 pthread_self() 取得 */
    long id = (long)arg;                         /* 方法 1：显式参数 */
    /* 方法 2：pthread_self(); 若想打印十六进制句柄 */
    printf("Hello from thread %ld\n", id);
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    /* 创建两个线程，传入不同编号 */
    pthread_create(&t1, NULL, say_hello, (void *)1L);   /* 返回 0 代表成功 :contentReference[oaicite:0]{index=0} */
    pthread_create(&t2, NULL, say_hello, (void *)2L);

    /* 等待两条子线程结束，回收资源 */
    pthread_join(t1, NULL);                             /* 会阻塞直到 t1 结束 :contentReference[oaicite:1]{index=1} */
    pthread_join(t2, NULL);

    puts("Main thread exits");
    return 0;
}

gcc -Wall -O2 simple_thread.c -pthread -o simple_thread    # -pthread 同时添加宏并链接 libpthread :contentReference[oaicite:2]{index=2}
./simple_thread

