#include <func.h>
struct mymsg{
    long mytype;
    char msg[128];
};
int main(int argc, char *argv[])
{
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}

