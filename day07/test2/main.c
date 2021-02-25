#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int fd_out = open(argv[1], O_WRONLY);
    ERROR_CHECK(fd_out, -1, "open");
    int fd_err = open(argv[2], O_WRONLY);
    ERROR_CHECK(fd_err, -1, "open");
    dup2(fd_out, STDOUT_FILENO);
    dup2(fd_err, STDERR_FILENO);
    perror("This is a standard error ouput\n");
    printf("This is a standard output\n");
    close(fd_out);
    close(fd_err);
    return 0;
}

