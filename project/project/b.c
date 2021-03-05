#include <func.h>
char pipe_name[2][7] = {"1.pipe", "2.pipe"};
void sigfunc(int signum){
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    kill(pid[0], 10);
    kill(pid[1], 10);
    kill(pid[2], 10);
    raise(10);
}
void sigfunc2(int signum){
    exit(0);
}
int main(){
    // open pipe
    system("clear");
    int fd_send = open(pipe_name[0], O_WRONLY);
    ERROR_CHECK(fd_send, -1, "open 2.pipe");
    int fd_reci = open(pipe_name[1], O_RDONLY);
    ERROR_CHECK(fd_reci, -1, "open 1.pipe");
    int msgid = msgget(1000, IPC_CREAT|0600);
    struct mymesg buff;
    buff.mtype = 1;
    fd_set rdset;
    int shm_pid = shmget(1001, 4096, IPC_CREAT|0600);
    pid_t *pid = (pid_t *)shmat(shm_pid, NULL, 0);
    pid[3] = getpid();
    while(1){
        signal(SIGINT, sigfunc);
        signal(10, sigfunc2);
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
            sprintf(messsage.mtext, "Mary %04d-%02d-%02d %02d:%02d:%02d\n%s",
                    local->tm_year+1900,
                    local->tm_mon+1,
                    local->tm_mday,
                    local->tm_hour,
                    local->tm_min,
                    local->tm_sec,
                    buf);
            messsage.mtype = 0;
            strcpy(buff.mtext, messsage.mtext);
            msgsnd(msgid, &buff, sizeof(buff.mtext), 0);
            write(fd_send, &messsage, sizeof(messsage));
            system("clear");
        }
        if(FD_ISSET(fd_reci, &rdset)){
            struct mymesg messsage;
            memset(&messsage, 0, sizeof(messsage));
            read(fd_reci, &messsage, sizeof(messsage));
            if(messsage.mtype == 0){
                strcpy(buff.mtext, messsage.mtext);
                msgsnd(msgid, &buff, sizeof(buff.mtext), 0);
            }
        }
    }
    close(fd_reci);
    close(fd_send);
    return 0;
}
