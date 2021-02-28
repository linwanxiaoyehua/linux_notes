#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 4);
    execl(argv[1], argv[1], argv[2], argv[3], NULL);
    return 0;
}

