<<<<<<< HEAD
#include <func.h>
=======
#include "../../func.h"
>>>>>>> 0e6287a69ee9c405571833ad71aa916aacdcab2d
char pipe_name[2][7] = {"1.pipe", "2.pipe"};
void out(){
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    int semArrid = semget(1000, 1, IPC_CREAT|0600);
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    int msgid = msgget(1000, IPC_CREAT|0600);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shm_pid, IPC_RMID, NULL);
    semctl(semArrid, 0, IPC_RMID);
    msgctl(msgid, IPC_RMID, NULL);
    unlink(pipe_name[0]);
    unlink(pipe_name[1]);
    exit(0);
}
void sigfunc(int signum){
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    kill(pid[0], 10);
    kill(pid[2], 10);
    kill(pid[3], 10);
    raise(10);
}
void sigfunc2(int signum){
    out();
}
int main(){
    system("clear");
    // make pipe
    int ret;
    ret = mkfifo(pipe_name[0], 0666);
    ERROR_CHECK(ret, -1, "mkfifo 1.pipe");
    ret = mkfifo(pipe_name[1], 0666);
    ERROR_CHECK(ret, -1, "mk 2.pipe");

    //signal
    // open pipe
    int fd_reci = open(pipe_name[0], O_RDONLY);
    ERROR_CHECK(fd_reci, -1, "open 1.pipe");
    int fd_send = open(pipe_name[1], O_WRONLY);
    ERROR_CHECK(fd_send, -1, "open 2.pipe");
    fd_set rdset;
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
    pid[1] = getpid();
    signal(SIGINT, sigfunc);
    signal(10, sigfunc2);
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fd_reci, &rdset);
        char buf[1024];
        select(fd_reci+1, &rdset, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &rdset)){
            memset(buf, 0, sizeof(buf));
            struct mymesg messsage;
            memset(&messsage, 0, sizeof(messsage));
            time_t time_now = time(NULL);
            struct tm *local;
            local = localtime(&time_now);
            read(STDIN_FILENO, buf, sizeof(buf));
            sprintf(messsage.mtext, "Jack %04d-%02d-%02d %02d:%02d:%02d\n%s",
                    local->tm_year+1900,
                    local->tm_mon+1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec,
                    buf);
            messsage.mtype = 0;
            semop(semArrid, &P, 1);
            strcpy(p, messsage.mtext);
            semop(semArrid, &V, 1);
            system("clear");
            write(fd_send, &messsage, sizeof(messsage));
        }
        if(FD_ISSET(fd_reci, &rdset)){
            struct mymesg messsage;
            memset(&messsage, 0, sizeof(messsage));
            read(fd_reci, &messsage, sizeof(messsage));
            if(messsage.mtype == 0){
                semop(semArrid, &P, 1);
                strcpy(p, messsage.mtext);
                semop(semArrid, &V, 1);
            }
        }
    }
    return 0;
}
