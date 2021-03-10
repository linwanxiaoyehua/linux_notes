/**
* @script:  code_3.c
* @brief    上面的模型有点不合理的地方，生产者需要一直运行，判断是否有余票，这样比较浪费资源。把上面的程序改变一下，使用两个条件变量，消费者卖完票后通知生产者，然后在1号条件变量上面等待生产者放票，生产者放票后通知消费者，然后在2号条件变量上面等待消费者把票卖完。
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-09
*/

#include <func.h>
typedef struct{
    int tickets;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    pthread_mutex_t mutex;
}Data_t;
void *saleOne(void *p){
    Data_t *pData = (Data_t *)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(0 != pData->tickets){
            printf("saleOne sells a ticket\n");
            --pData->tickets;
            if(0 == pData->tickets){
                pthread_cond_signal(&pData->cond2);
            }
        }
        else{
            pthread_cond_wait(&pData->cond1, &pData->mutex);
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *saleTwo(void *p){
    Data_t *pData = (Data_t *)p;
    while(1){
        pthread_mutex_lock(&pData->mutex);
        if(0 != pData->tickets){
            printf("saleTwo sells a ticket\n");
            --pData->tickets;
            if(0 == pData->tickets){
                pthread_cond_signal(&pData->cond2);
            }
        }
        else{
            pthread_cond_wait(&pData->cond1, &pData->mutex);
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *setTicket(void *p){
    Data_t *pData = (Data_t *)p;
    pthread_mutex_lock(&pData->mutex);
    if(0 != pData->tickets){
        pthread_cond_wait(&pData->cond2, &pData->mutex);
    }
    pData->tickets += 10;
    pthread_cond_broadcast(&pData->cond1);
    printf("add 10 tickets\n");
    pthread_mutex_unlock(&pData->mutex);
    pthread_exit(NULL);
}
int main(int argc, char **agrv){
    Data_t data;
    data.tickets = 10;
    pthread_cond_init(&data.cond1, NULL);
    pthread_cond_init(&data.cond2, NULL);
    pthread_mutex_init(&data.mutex, NULL);
    pthread_t thid_saleOne, thid_saleTwo, thid_setTicket;
    pthread_create(&thid_saleOne, NULL, saleOne, &data);
    pthread_create(&thid_saleTwo, NULL, saleTwo, &data);
    pthread_create(&thid_setTicket, NULL, setTicket, &data);
    pthread_join(thid_saleOne, NULL);
    pthread_join(thid_saleTwo, NULL);
    pthread_join(thid_setTicket, NULL);
    pthread_mutex_destroy(&data.mutex);
    pthread_cond_destroy(&data.cond1);
    pthread_cond_destroy(&data.cond2);
    return 0;
}
