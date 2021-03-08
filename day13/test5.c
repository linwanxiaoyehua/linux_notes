/**
* @script:  test5.c
* @brief    使用真实计时器，实用计时器，统计程序执行时间，在实用计时器及虚拟计时器设定计时后，先睡眠，再让程序处于while（1）
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
void sigfunc(int signum){
    time_t now = time(NULL);
    puts(ctime(&now));
}
int main(){
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigfunc;
    sigaction(SIGALRM, &act, NULL);
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 3;
    timer.it_interval.tv_usec = 0;
/*
 * 将这里的ITIMER_REAL改为ITIMER_PROF即为实用时间
 */
    setitimer(ITIMER_REAL, &timer, NULL);
    sigfunc(0);
    sleep(2);
    while(1);
    return 0;
}
