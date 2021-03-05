#include <func.h>
void sigfunc(int signum){
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    kill(pid[0], 10);
    kill(pid[1], 10);
    kill(pid[3], 10);
    raise(10);
}
void sigfunc2(int signum){
    exit(0);
}
int main(){
    system("clear");
    int msgid = msgget(1000, IPC_CREAT|0600);
    struct mymesg buf;
    memset(&buf, 0, sizeof(buf));
    char mess[1100] = {0};
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    pid[2] = getpid();
    while(1){
        signal(SIGINT, sigfunc);
        signal(10, sigfunc2);
        msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0);
        if(strcmp(mess, buf.mtext)){
            printf("%s", buf.mtext);
            strcpy(mess, buf.mtext);
        }

    }
    return 0;
}
