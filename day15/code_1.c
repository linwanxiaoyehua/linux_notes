/**
* @script:  add.c
* @brief    主线程定义一个整形数num=0，创建2个子线程，通过传参的方式把num传给子线程，让两个子线程分别对这个num各加1000万，通过使用互斥锁，让两个子线程每次加完1000万后的结果都是2000万，注意使用清理函数，保证锁资源的释放。
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-08
*/

/**
 *Q: 加锁和解锁应该放在for循环的外面还是for循环里面，为什么？
 *A: 放在内部，因为++res是一个原子操作，但是整个for循环不是
 *Q: 现在子线程里需要对num加一，也需要对同一把互斥锁加锁和解锁，如何把互斥锁和num同时传给子线程，让子线程能够加解锁和加一。
 *A: 设置全局变量，或者设置一个结构体，内部包含一个锁以及整型变量
 */
#include <func.h>
int res = 0;
void cleanFunc(void *p){
    pthread_mutex_t *pMutex = (pthread_mutex_t *)p;
    pthread_mutex_destroy(pMutex);
}
void *addOne(void *p){
    pthread_mutex_t *pMutex = (pthread_mutex_t *)p;
    for(int i = 0; i < 10000000; ++i){
        pthread_mutex_lock(pMutex);
        ++res;
        pthread_mutex_unlock(pMutex);
    }
    pthread_exit(NULL);
}
void *addTwo(void *p){
    pthread_mutex_t *pMutex = (pthread_mutex_t *)p;
    for(int i = 0; i < 10000000; ++i){
        pthread_mutex_lock(pMutex);
        ++res;
        pthread_mutex_unlock(pMutex);
    }
    pthread_exit(NULL);
}
int main(int argc, char **argv){
    //锁初始化
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    //线程创建
    pthread_t thid_addOne, thid_addTwo;
    pthread_cleanup_push(cleanFunc, &mutex);
    int ret = pthread_create(&thid_addOne, NULL, addOne, &mutex);
    THREAD_ERROR_CHECK(ret, "creat thread addOne");
    ret = pthread_create(&thid_addTwo, NULL, addTwo, &mutex);
    THREAD_ERROR_CHECK(ret, "creat thread addTwo");
    pthread_join(thid_addOne, NULL);
    pthread_join(thid_addTwo, NULL);
    pthread_cleanup_pop(1);
    printf("res = %d\n", res);
    pthread_mutex_destroy(&mutex);
    return 0;
}
