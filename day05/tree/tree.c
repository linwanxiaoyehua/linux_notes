#include <func.h>
int DFSprint(char *path, int width);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    printf("%s\n", argv[1]);
    DFSprint(argv[1], 1);
    return 0;
}
int DFSprint(char *path, int width){
    char new_path[1024] = {0};
    DIR *pDir = opendir(path);
    ERROR_CHECK(pDir, NULL, "opendir");
    struct dirent *pDirent;
    while(pDirent = readdir(pDir)){
        if(strcmp(pDirent->d_name, ".") == 0 ||
           strcmp(pDirent->d_name, "..") == 0 ||
           pDirent->d_name[0] == '.'){
            continue;
        };
        for(int i = 0; i < 5*(width-1); i++){
            printf(" ");
        }
        for(int i = 0; i < 4; i++){
            printf("-");
        }
        printf("%s\n", pDirent->d_name);
        if(pDirent->d_type == DT_DIR){
            sprintf(new_path, "%s%s%s", path, "/", pDirent->d_name);
            DFSprint(new_path, width+1);
        }
    }
    return 0;
}
