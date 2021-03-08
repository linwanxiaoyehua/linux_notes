/**
* @script:  test4.h
* @brief    通过sigpromask阻塞2号信号，睡眠5秒后，解除阻塞，2号信号得到执行；在睡眠后，解除阻塞之前，通过sigpending检测是否有信号挂起
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
int main(){
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    int ret = sigprocmask(SIG_BLOCK, &mask, NULL);
    ERROR_CHECK(ret, -1, "sigprocmask");
    printf("Block begin!\n");
    sleep(5);
    sigset_t pendingSet;
    sigpending(&pendingSet);
    if(sigismember(&pendingSet, SIGINT)){
        printf("sigint is pending!\n");
    }else{
        printf("sigint isn't pending!\n");
    }
    ret = sigprocmask(SIG_UNBLOCK, &mask, NULL);
    ERROR_CHECK(ret, -1, "sigprocmask");
    printf("Block end!\n");
    while(1);
    return 0;
}
