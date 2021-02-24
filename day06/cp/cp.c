#include <func.h>

int main(int argc, char *argv[3])
{
    ARGS_CHECK(argc, 3);
    int input = open(argv[1], O_RDONLY);
    ERROR_CHECK(input, -1, "open");
    int output = open(argv[2], O_WRONLY|O_CREAT, 0666);
    ERROR_CHECK(output, -1, "open");
    char buf[40960] = {0};
    while(1){
        memset(buf, 0, sizeof(buf));
        int ret = read(input, buf, sizeof(buf));
        if(ret == 0){
            break;
        }
        write(output, buf, ret);
    }
    close(input);
    close(output);
    return 0;
}

