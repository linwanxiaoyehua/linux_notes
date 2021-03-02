#include <func.h>

int main(int argc, char *argv[])
{
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    int *p = (int *)shmat(shmid, NULL, 0);
    p[0] = 0;
    pid_t pid = fork();
    int flag[2] = {0};
    int turn;
    if(pid == 0){
        for(int i = 0; i < 20000000; ++i){
            flag[0] = 1;
            turn = 1;
            while(flag[1] && turn == 1){
            }
            ++p[0];
            flag[1] = 0;
        }
    }else{
        for(int i = 0; i < 20000000; ++i){
            flag[1] = 1;
            turn = 0;
            while(flag[0] && turn == 0){
            }
            ++p[0];
            flag[0] = 0;
        }
        wait(NULL);
        printf("p[0] = %d\n", p[0]);
    }
    return 0;
}

