#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    write(fd, "world", 5);
    char buf[10] = {0};
    int new_fd = dup(fd);
    lseek(new_fd, 0, SEEK_SET);
    read(new_fd, buf, 4);
    puts(buf);
    close(fd);
    close(new_fd);
    return 0;
}

