/**
* @script:  test3.c
* @brief    通过sigaction，打印发送信号的发送者的pid和uid
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
void sigfunc(int signum, siginfo_t *info, void *p){
    printf("pid = %d\n", info->si_pid);
    printf("uid = %d\n", info->si_uid);
}
int main(){
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigfunc;
    int ret = sigaction(SIGINT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction");
    while(1);
    return 0;
}
