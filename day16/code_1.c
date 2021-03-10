/**
 * @script:  code_1.c
 * @brief    我们知道线程访问一些资源时要先加锁，加锁成功的线程，代表抢到了资源，那么多个线程竞争一把锁时，锁能不能保证公平性，能不能保证资源是平均分配给多个线程的？设计一个程序验证一下锁的公平性。
 * @author   xiaoyehua<me@xiaoyehua.net>
 * @version  1.0.0
 * @modify   2021-03-09
 */

#include <func.h>
typedef struct {
    int num;
    int thread1;
    int thread2;
    pthread_mutex_t mutex;
}Data_t;
void *threadFunc1(void *p){
    Data_t *pData = (Data_t *)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(pData->num != 0){
            --pData->num;
            ++pData->thread1;
        }else{
            pthread_mutex_unlock(&pData->mutex);
            break;
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *threadFunc2(void *p){
    Data_t *pData = (Data_t *)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(pData->num != 0){
            --pData->num;
            ++pData->thread2;
        }else{
            pthread_mutex_unlock(&pData->mutex);
            break;
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv){
    Data_t data;
    data.num = 10000000;
    data.thread1 = 0;
    data.thread2 = 0;
    pthread_mutex_init(&data.mutex, NULL);
    pthread_t thid1, thid2;
    int ret = 0;
    ret = pthread_create(&thid1, NULL, threadFunc1, &data);
    THREAD_ERROR_CHECK(ret, "create thread 1");
    ret = pthread_create(&thid2, NULL, threadFunc2, &data);
    THREAD_ERROR_CHECK(ret, "create thread 2");
    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    printf("threadFunc1 = %d, threadFunc2 = %d\n", data.thread1, data.thread2);
    pthread_mutex_destroy(&data.mutex);
    return 0;
}

