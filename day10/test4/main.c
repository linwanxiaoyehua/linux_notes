#include <func.h>

int main(int argc, char *argv[])
{
    int shmid = shmget(1000, 4096, IPC_CREAT|0600);
    char *p = (char *)shmat(shmid, NULL, 0);
    strcpy(p, "How are you");
    return 0;
}

