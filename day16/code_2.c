/**
* @script:  code_2.c
* @brief    编写一个生产者消费者卖票放票的程序，一个生产者，两个消费者，消费者有票就卖票，没有票时等待通知，生产者运行时如果发现没票了，就放票出来，然后通知消费者卖票。
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-09
*/
#include <func.h>
typedef struct{
    int tickets;
    pthread_cond_t cond;
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
                pthread_cond_signal(&pData->cond);
            }
        }
        else{
            pthread_cond_signal(&pData->cond);
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
                pthread_cond_signal(&pData->cond);
            }
        }
        else{
            pthread_cond_signal(&pData->cond);
        }
        pthread_mutex_unlock(&pData->mutex);
    }
    pthread_exit(NULL);
}
void *setTicket(void *p){
    Data_t *pData = (Data_t *)p;
    pthread_mutex_lock(&pData->mutex);
    if(0 != pData->tickets){
        pthread_cond_wait(&pData->cond, &pData->mutex);
    }
    pData->tickets += 10;
    printf("add 10 tickets\n");
    pthread_mutex_unlock(&pData->mutex);
    pthread_exit(NULL);
}
int main(int argc, char **agrv){
    Data_t data;
    data.tickets = 10;
    pthread_cond_init(&data.cond, NULL);
    pthread_mutex_init(&data.mutex, NULL);
    pthread_t thid_saleOne, thid_saleTwo, thid_setTicket;
    pthread_create(&thid_saleOne, NULL, saleOne, &data);
    pthread_create(&thid_saleTwo, NULL, saleTwo, &data);
    pthread_create(&thid_setTicket, NULL, setTicket, &data);
    pthread_join(thid_saleOne, NULL);
    pthread_join(thid_saleTwo, NULL);
    pthread_join(thid_setTicket, NULL);
    pthread_mutex_destroy(&data.mutex);
    pthread_cond_destroy(&data.cond);
    return 0;
}
