#include <func.h>
void sigfunc(int signum){
    printf("signum = %d\n", signum);
    exit(0);
}
int main(int argc, char *argv[])
{
    sighandler_t ret = signal(SIGINT, sigfunc);
    ERROR_CHECK(ret, SIG_ERR, "signal");
    puts("process begin");
    while(1);
    return 0;
}

