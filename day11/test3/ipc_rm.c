#include <func.h>

int main(int argc, char *argv[])
{
    int semArrid = semget(1000, 2, 0);
    ERROR_CHECK(semArrid, -1, "semget");
    semctl(semArrid, 0, IPC_RMID);
    return 0;
}

