#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <setjmp.h>
#include <pthread.h>
typedef void (*sighandler_t)(int);
#define ARGS_CHECK(argc,num) {if(argc != num)\
	{fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret == num)\
	{perror(msg);return -1;}}
#define THREAD_ERROR_CHECK(ret, funcName) \
	do { \
		if (0 != ret) { \
			printf("%s : %s\n", funcName, strerror(ret)); \
		} \
	} while(0)
