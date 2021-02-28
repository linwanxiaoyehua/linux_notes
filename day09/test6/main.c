#include <func.h>
int mySystem(char *command){
    if(command == NULL){
        printf("Empty command\n");
        return -1;
    }
    pid_t pid = fork();
    int status;
    if(pid < 0){
        status = -1;
    }
    else if(pid == 0){
        execl("/bin/sh", "sh", "-c", command, (char *)0);
        exit(0);
    }else if(wait(&status) < 0){
        printf("Error\n");
        return -1;
    }
}
int main(int argc, char *argv[])
{
    char *command = (char *)calloc(1, 1000*sizeof(char));
    for(int i = 1; i < argc; ++i){
        if(i != 1) strcat(command, " ");
        strcat(command, argv[i]);
    }
    mySystem(command);
    return 0;
}

