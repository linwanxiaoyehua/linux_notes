#include <func.h>
//A用户编写一个程序，用来往file文件中写入内容hello，然后编译后，增加s权限，这时B用户执行该程序，能够往file文件中写入hello。
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_WRONLY);
    ERROR_CHECK(fd, -1, "open");
    write(fd, "hello\n", 6);
    close(fd);
    return 0;
}

