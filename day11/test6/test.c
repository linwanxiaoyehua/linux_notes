#include <func.h>

int main(int argc, char *argv[])
{
    int semArrid = semget(1000, 1, IPC_CREAT|0600);
    ERROR_CHECK(semArrid, -1, "semget")
    return 0;
}

