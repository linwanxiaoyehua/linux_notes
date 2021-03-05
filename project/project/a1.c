#include <func.h>
void sigfunc(int signum){
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    kill(pid[1], 10);
    kill(pid[2], 10);
    kill(pid[3], 10);
    raise(10);
}
void sigfunc2(int signum){
    exit(0);
}
int main(){
    system("clear");
    int semArrid = semget(1000, 1, IPC_CREAT|0600);
    semctl(semArrid, 0, SETVAL, 1);
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    struct sembuf V;
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    char *p = (char *)shmat(shmid, NULL, 0);
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    pid[0] = getpid();
    char mes[1100] = {0};
    while(1){
        signal(SIGINT, sigfunc);
        signal(10, sigfunc2);
        if(strcmp(p, mes)){
            semop(semArrid, &P, 1);
            printf("%s", p);
            semop(semArrid, &V, 1);
            strcpy(mes, p);
        }
    }
    return 0;
}
