#include <func.h>

int main(int argc, char *argv[])
{
    int semArrid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semArrid, -1, "semget");
    int ret = semctl(semArrid, 0, SETVAL, 5);
    ERROR_CHECK(ret, -1, "semctl GETVAL");
    struct sembuf P;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    semop(semArrid, &P, 1);
    int val = semctl(semArrid, 0, GETVAL);
    ERROR_CHECK(val, -1, "semctl GETVAL");
    printf("get val = %d\n", val);
    return 0;
}

