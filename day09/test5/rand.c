#include <func.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    if(left > right){
        int temp = left;
        left = right;
        right = temp;
    }
    srand(time(NULL));
    int ret = rand()%right + left;
    printf("The random num between %d and %d is %d\n", left, right, ret);
    return 0;
}

