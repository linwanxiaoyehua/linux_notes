/**
* @script:  test2.c
* @brief    sigaction注册2号信号的处理函数，在处理2号信号时阻塞3号信号，不会被三号信号打断，同时在2号信号的信号处理函数中，判断一下有没有3号信号被挂起
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
void sigfunc(int signum, siginfo_t *info, void *p){
    printf("before, signum = %d\n", signum);
    sleep(3);
    sigset_t pendingSet;
    sigpending(&pendingSet);
    if(sigismember(&pendingSet, SIGQUIT)){
        printf("SIGQUIT is pending!\n");
    }else{
        printf("SIGQUIT isn't pending!\n");
    }
    printf("after, signum = %d\n", signum);
}
int main(){
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigfunc;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    int ret = sigaction(SIGINT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction sigint");
    ret = sigaction(SIGQUIT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction sigquit");
    while(1);
    return 0;
}

