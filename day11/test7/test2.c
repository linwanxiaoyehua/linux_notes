#include <func.h>
struct mymsg{
    long mytype;
    char msg[128];
};
int main(int argc, char *argv[])
{
    int msgid = msgget(1000, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    struct mymsg buf;
    memset(&buf, 0, sizeof(buf));
    int ret = msgrcv(msgid, &buf, sizeof(buf.msg), 1, 0);
    ERROR_CHECK(ret, -1, "msgrcv");
    printf("type = %ld, msg = %s\n", buf.mytype, buf.msg);
    return 0;
}

