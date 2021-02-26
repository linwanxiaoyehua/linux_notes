#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd_read = open(argv[1], O_RDWR);
    ERROR_CHECK(fd_read, -1, "open");
    int fd_write = open(argv[1], O_RDWR);
    ERROR_CHECK(fd_write, -1, "open");
    fd_set rd_set;
    fd_set wr_set;
    char rd_buf[2048];
    char wr_buf[2048];
    while(1){
        FD_ZERO(&rd_set);
        FD_ZERO(&wr_set);
        FD_SET(STDIN_FILENO, &wr_set);
        FD_SET(fd_read, &rd_set);
        select(fd_read+1, &rd_set, &wr_set, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &wr_set)){
            memset(wr_buf, 0, sizeof(wr_buf));
            read(STDIN_FILENO, wr_buf, sizeof(wr_buf)-1);
            write(fd_write, wr_buf, sizeof(wr_buf)-1);
            printf("Write: %s", wr_buf);
        }
        if(FD_ISSET(fd_read, &rd_set)){
            memset(rd_buf, 0, sizeof(rd_buf)-1);
            read(fd_read, rd_buf, sizeof(rd_buf)-1);
            printf("Read: %s", rd_buf);
        }
    }
    close(fd_read);
    close(fd_write);
    return 0;
}

