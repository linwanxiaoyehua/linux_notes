#include <func.h>

int main(){
    int shmid = shmget(1000, 4096, 0600|IPC_CREAT);
    ERROR_CHECK(shmid, -1, "shmget");
    char *p = (char *)shmat(shmid, NULL, 0);
    ERROR_CHECK(p, (char *)-1, "shmat");
    char message[1100] = {0};
    printf("Chat with Jack\n");
    while(1){
        if(strcmp(p, message)){
            printf("%s", p);
            memset(message, 0, sizeof(message));
            strcpy(message, p);
        }
    }
    return 0;
}
