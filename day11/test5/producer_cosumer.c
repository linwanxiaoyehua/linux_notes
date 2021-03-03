#include <func.h>

int main(int argc, char *argv[])
{
    int semArrid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semArrid, -1, "semget");
    int ret = semctl(semArrid, 0, SETVAL, 1);
    ERROR_CHECK(ret, -1, "semctl");
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_op = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    ERROR_CHECK(shmid, -1, "shmget");
    int *p = (int *)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (int *)-1, "shmat");
    p[0] = 0;
    p[1] = 6;
    pid_t pid = fork();
    if(pid == 0){
        while(1){
            sleep(2);
            printf("I'm cosumer, before cosume, space = %d, goods = %d\n",
                   p[1], p[0]);
            semop(semArrid, &P, 1);
            if(p[0] > 0){
                --p[0];
                printf("buy goods\n");
                ++p[1];
            }
            printf("I'm cosumer, after cosume, space = %d, goods = %d\n",
                   p[1], p[0]);
        }
    }else{
        while(1){
            sleep(1);
            printf("I'm producer, before produce, space = %d, goods = %d\n",
                   p[1], p[0]);
            semop(semArrid, &P, 1);
            if(p[1] > 0){
                --p[1];
                printf("produce goods\n");
                ++p[0];
            }
            printf("I'm producer, after produce, space = %d, goods = %d\n",
                   p[1], p[0]);
        }
        semctl(semArrid, 0, IPC_RMID);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

