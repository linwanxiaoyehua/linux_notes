#include <func.h>
void Daemon(){
    const int MAXFD = 64;
    if(fork() != 0){
        exit(0);
    }
    setsid();
    chdir("/");
    umask(0);
    for(int i = 0; i < MAXFD; ++i){
        close(i);
    }
}
int main(int argc, char *argv[])
{
    Daemon();
    int fd = open("/tmp/file", O_WRONLY|O_CREAT|O_APPEND, 0666);
    while(1){
        time_t time_now = time(NULL);
        char str_time[100] = {0};
        strcpy(str_time, ctime(&time_now));
        write(fd, str_time, strlen(str_time));
        sleep(10);
    }
    return 0;
}

