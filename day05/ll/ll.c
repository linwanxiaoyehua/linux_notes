#include <func.h>
void print_mode(struct stat statBuf);
int main(int argc, char *argv[]){
    char mon[12][4] = {"Jan", "Feb", "Mar", "Apr", "May",
        "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    ARGS_CHECK(argc, 2);
    DIR *pDir = opendir(argv[1]);
    ERROR_CHECK(pDir, NULL, "opendir");
    chdir(argv[1]);
    struct dirent *pDirent;
    while((pDirent = readdir(pDir))){
        if(strcmp(pDirent->d_name, ".") == 0 
           || strcmp(pDirent->d_name, "..") == 0){
            continue;
        }
        struct stat statBuf;
        int ret = stat(pDirent->d_name, &statBuf);
        ERROR_CHECK(ret, -1, "stat");
        print_mode(statBuf);
        struct tm *local;
        local = localtime(&(statBuf.st_mtime));
        printf(" %ld %s %s %7ld %s %2d %2d:%2d %s\n", 
               statBuf.st_nlink, 
               getpwuid(statBuf.st_uid)->pw_name, 
               getgrgid(statBuf.st_gid)->gr_name,
               statBuf.st_size,
               mon[local->tm_mon],
               local->tm_mday,
               local->tm_hour,
               local->tm_min,
               pDirent->d_name
               );
    }
    return 0;
}
void print_mode(struct stat statBuf) {
    mode_t mode = statBuf.st_mode;
    char str[11] = {0};
    //判断文件类型
    if(S_ISLNK(mode)){
        str[0] = 'l';
    }
    if(S_ISREG(mode)){
        str[0] = '-';
    }
    if(S_ISDIR(mode)){
        str[0] = 'd';
    }
    if(S_ISCHR(mode)){
        str[0] = 'c';
    }
    if(S_ISBLK(mode)){
        str[0] = 'b';
    }
    if(S_ISFIFO(mode)){
        str[0] = 'p';
    }
    if(S_ISSOCK(mode)){
        str[0] = 's';
    }
    if(mode & S_IRUSR){
        str[1] = 'r';
    }
    if(mode & S_IWUSR){
        str[2] = 'w';
    }
    if(mode & S_IXUSR){
        str[3] = 'x';
    }
    if(mode & S_IRGRP){
        str[4] = 'r';
    }
    if(mode & S_IWGRP){
        str[5] = 'w';
    }
    if(mode & S_IXGRP){
        str[6] = 'x';
    }
    if(mode & S_IROTH){
        str[7] = 'r';
    }
    if(mode & S_IWOTH){
        str[8] = 'w';
    }
    if(mode & S_IXOTH){
        str[9] = 'x';
    }
    for(int i = 0; i < 10; i++){
        printf("%c", str[i]==0 ? '-' : str[i]);
    }
}
