//使用select实现即时聊天，要发送本机时间给对方显示，支持超时和退出机制
#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int fd_send = open(argv[1], O_WRONLY);
    ERROR_CHECK(fd_send, -1, "open");
    int fd_reci = open(argv[2], O_RDONLY);
    ERROR_CHECK(fd_reci, -1, "open");
    puts("Chating with Mary");
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fd_reci, &rdset);
        char buf[1024];
        struct timeval timeout;
        timeout.tv_sec = 100;
        timeout.tv_usec = 10000000;
        if(select(fd_reci+1, &rdset, NULL, NULL, &timeout) == 0) {
            puts("Timeout! Chat Shut down Now!");
            break;
        } else {
            if(FD_ISSET(STDIN_FILENO, &rdset)){
                memset(buf, 0, sizeof(buf));
                char message[1100] = {0};
                time_t time_now = time(NULL);
                struct tm *local;
                local = localtime(&time_now);
                if(read(STDIN_FILENO, buf, sizeof(buf)-1) == 0){
                    printf("Now quitting chat!\n");
                    sprintf(message, "Mary %04d-%02d-%02d %02d:%02d:%02d\nI'm leaving now!", 
                            local->tm_year+1900, 
                            local->tm_mon+1, 
                            local->tm_mday, 
                            local->tm_hour, 
                            local->tm_min, 
                            local->tm_sec);
                    write(fd_send, message, sizeof(message));
                    break;
                }
                sprintf(message, "Mary %04d-%02d-%02d %02d:%02d:%02d\n%s", 
                            local->tm_year+1900, 
                            local->tm_mon+1, 
                            local->tm_mday, 
                            local->tm_hour, 
                            local->tm_min, 
                            local->tm_sec, 
                            buf);

                printf("\b\r%s", message);
                write(fd_send, message, sizeof(message));
            }
            if(FD_ISSET(fd_reci, &rdset)){
                char message[1100] = {0};
                if(read(fd_reci, message, sizeof(buf)-1) == 0){
                    printf("%s", message);
                    break;
                }
                printf("%s", message);
            }
        }
    }
    close(fd_reci);
    close(fd_send);
    return 0;
}

