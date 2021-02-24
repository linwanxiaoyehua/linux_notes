#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    char *p = (char *)mmap(NULL, 5, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");
    p[0] = 'w';
    p[1] = 'o';
    p[2] = 'r';
    p[3] = 'l';
    p[4] = 'd';
    munmap(p, 5);
    close(fd);
    return 0;
}

