#include <func.h>
//编写程序，打印当前进程pid，父进程pid，真实用户ID，真实组ID，有效用户ID，有效组ID
int main()
{
    printf("pid = %d, ppid = %d, uid = %d, euid = %d, gid = %d, egid = %d\n",
           getpid(),
           getppid(),
           getuid(),
           geteuid(),
           getgid(),
           getegid());
    return 0;
}

