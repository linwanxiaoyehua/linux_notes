#include <func.h>
struct mymsg{
    long mytype;
    char msg[128];
};
int main(int argc, char *argv[])
{
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    struct mymsg buf[3];
    for(int i = 0; i < 3; ++i){
        buf[i].mytype = i+1;
        sprintf(buf[i].msg, "%d", i);
        msgsnd(msgid, &buf, strlen(buf[i].msg), 0);
    }
    return 0;
}

