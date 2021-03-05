#include <func.h>
struct mymsg{
    long mytype;
    char mtext[1100];
};
int main(){
    char message[1100] = {0};
    while(1){
    int msgid = msgget(1001, IPC_CREAT|0600);
    ERROR_CHECK(msgid, -1, "msgget");
    struct mymsg buf;
        memset(&buf, 0, sizeof(buf));
        if(msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0)){
            printf("%s", buf.mtext);
        }
    }
    
    return 0;
}
