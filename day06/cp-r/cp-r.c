#include <func.h>
int cp(char *in, char *out);
int DFScp(char *in, char *out);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    mkdir(argv[2], 0777);
    DFScp(argv[1], argv[2]);
    return 0;
}
int DFScp(char *in, char *out){
    char new_in[1024] = {0};
    char new_out[1024] = {0};
    DIR *pDir = opendir(in);
    ERROR_CHECK(pDir, NULL, "opendir");
    struct dirent *pDirent;
    while(pDirent = readdir(pDir)){
        if(strcmp(pDirent->d_name, ".") == 0 ||
           strcmp(pDirent->d_name, "..") == 0){
            continue;
        }
        sprintf(new_in, "%s%s%s", in, "/", pDirent->d_name);
        sprintf(new_out, "%s%s%s", out, "/", pDirent->d_name);
        if(pDirent->d_type == DT_DIR){
            mkdir(new_out, 0777);
            DFScp(new_in, new_out);
        }else{
            cp(new_in, new_out);
        }
    }
    return 0;
}
int cp(char *in, char *out){
    int input = open(in, O_RDONLY);
    ERROR_CHECK(input, -1, "open");
    int output = open(out, O_WRONLY|O_CREAT, 0666);
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

