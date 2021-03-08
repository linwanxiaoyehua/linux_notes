/**
* @script:  test1.c
* @brief    sigaction实现信号不断重入的执行效果（来回打断的效果）
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
void sigfunc(int signum){
    printf("before, signum = %d\n", signum);
    sleep(3);
    printf("after, signum = %d\n", signum);
}
int main(){
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigfunc;
    act.sa_flags = SA_NODEFER;
    int ret = sigaction(SIGINT, &act, NULL);
    ERROR_CHECK(ret, -1, "sigaction");
    while(1);
    return 0;
}
