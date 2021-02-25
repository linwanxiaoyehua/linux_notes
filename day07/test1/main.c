#include <func.h>
typedef struct student{
    int id;
    char name[20];
    int grade;
}STU;
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    STU stu[3];
    memset(stu, 0, sizeof(stu));
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    for(int i = 0; i < 3; i++){
        scanf("%d %s %d", &stu[i].id, stu[i].name, &stu[i].grade);
        char buf[50] = {0};
        sprintf(buf, "%d %s %d\n", stu[i].id, stu[i].name, stu[i].grade);
        write(fd, buf, sizeof(buf));
    }
    lseek(fd, 0, SEEK_SET);
    for(int i = 0; i < 3; i++){
        char buf[50] = {0};
        read(fd, buf,sizeof(buf));
        printf("%s", buf);
    }
    close(fd);
    return 0;
}

