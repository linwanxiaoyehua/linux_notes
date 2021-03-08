/**
* @script:  test6.c
* @brief    实现一个自己的kill命令，传参是传入信号处理编号和进程id
* @author   xiaoyehua<me@xiaoyehua.net>
* @version  1.0.0
* @modify   2021-03-07
*/

#include <func.h>
int main(int argc, char **argv){
    ARGS_CHECK(argc, 3);
    int sig = atoi(argv[1]+1);
    pid_t pid = atoi(argv[2]);
    kill(pid, sig);
    return 0;
}
