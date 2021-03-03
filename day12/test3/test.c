#include <func.h>
void sigfunc(int signum){
    printf("before signum = %d\n", signum);
    sleep(4);
    printf("after signum = %d\n", signum);
}
int main(int argc, char *argv[])
{
    sighandler_t ret1 = signal(SIGINT, sigfunc);
    ERROR_CHECK(ret1, SIG_ERR, "signal");
    sighandler_t ret2 = signal(SIGQUIT, sigfunc);
    ERROR_CHECK(ret2, SIG_ERR, "signal");
    puts("process begin");
    while(1);
    return 0;
}

