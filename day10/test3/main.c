#include <func.h>

int main(int argc, char *argv[])
{
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if(pid == 0){
        close(fds[1]);
        char buf[6] = {0};
        read(fds[0], buf, sizeof(buf-1));
        printf("%s", buf);
        exit(0);
    }else{
        close(fds[0]);
        printf("world");
        write(fds[1], "hello", 5);
        wait(NULL);
    }
    return 0;
}

