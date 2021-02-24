#include <func.h>
void get_mode(mode_t mode, char *str);
void print_type(char c);
void print_time(time_t time);
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    struct stat statBuf;
    int ret = stat(argv[1], &statBuf);
    ERROR_CHECK(ret, -1, "stat");
    char str[11] = {0};
    get_mode(statBuf.st_mode, str);
    printf(" File: %s\n Size: %-10ld\tBlocks: %-11ldIO Block: %-8ld", 
           argv[1], 
           statBuf.st_size, 
           statBuf.st_blocks,
           statBuf.st_blksize);
    print_type(str[0]);
    printf("Device: %lxh/%ldd\t Inode: %-12ld Links: %ld\n",
           statBuf.st_dev,
           statBuf.st_dev, 
           statBuf.st_ino, 
           statBuf.st_nlink);
    char buf[10] = {0};
    sprintf(buf, "%o", statBuf.st_mode);
    printf("Access: (%s/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
           buf+1,
           str,
           statBuf.st_uid,
           getpwuid(statBuf.st_uid)->pw_name,
           statBuf.st_gid,
           getgrgid(statBuf.st_gid)->gr_name);
    printf("Access: ");
    print_time(statBuf.st_atime);
    printf("Modify: ");
    print_time(statBuf.st_mtime);
    printf("Change: ");
    print_time(statBuf.st_ctime);
    return 0;
}
void print_time(time_t time){
    struct tm *local;
    local = localtime(&time);
    printf("%04d-%02d-%02d %02d:%02d:%02d %s\n",
           local->tm_year+1900,
           local->tm_mon+1,
           local->tm_mday,
           local->tm_hour,
           local->tm_hour,
           local->tm_sec,
           local->tm_zone);
}
void print_type(char c){
    if(c == 'l') printf("symbolic link\n");
    if(c == '-') printf("regular file\n");
    if(c == 's') printf("socket\n");
    if(c == 'b') printf("block device\n");
    if(c == 'd') printf("directory\n");
    if(c == 'c') printf("character file\n");
    if(c == 'p') printf("FIFO\n");
}
void get_mode(mode_t mode, char *str){
    if(S_ISLNK(mode)) str[0] = 'l';
    if(S_ISREG(mode)) str[0] = '-';
    if(S_ISSOCK(mode)) str[0] = 's';
    if(S_ISBLK(mode)) str[0] = 'b';
    if(S_ISDIR(mode)) str[0] = 'd';
    if(S_ISCHR(mode)) str[0] = 'c';
    if(S_ISFIFO(mode)) str[0] = 'p';
    if(mode & S_IRUSR) str[1] = 'r';
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';
    if(mode & S_IRGRP) str[4] = 'r';
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';
    if(mode & S_IROTH) str[7] = 'r';
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
    for(int i = 0; i < 10; i++){
        if(str[i] == 0){
            str[i] = '-';
        }
    }
}

