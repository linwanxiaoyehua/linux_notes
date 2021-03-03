# 使用semctl执行下列命令：SETVAL，GETVAL，SETALL，GETALL，IPC_RMID
```bash
[me@xiaoyehua ~/github/day11/test3]$ vim setval_getval.c
[me@xiaoyehua ~/github/day11/test3]$ make
gcc setval_getval.c -o setval_getval
[me@xiaoyehua ~/github/day11/test3]$ ./setval_getval 
get val = 4
[me@xiaoyehua ~/github/day11/test3]$ vim setall_getall.c
[me@xiaoyehua ~/github/day11/test3]$ make
gcc setall_getall.c -o setall_getall
[me@xiaoyehua ~/github/day11/test3]$ ./setall_getall 
GETALL result: 
origin arr[0] = 1; res arr[0] = 1
origin arr[1] = 2; res arr[1] = 2
origin arr[2] = 3; res arr[2] = 3
origin arr[3] = 4; res arr[3] = 4
origin arr[4] = 5; res arr[4] = 5
[me@xiaoyehua ~/github/day11/test3]$ vim setall_getall.c
[me@xiaoyehua ~/github/day11/test3]$ make
gcc setall_getall.c -o setall_getall
[me@xiaoyehua ~/github/day11/test3]$ ./setall_getall 
GETALL result before: 
origin arr[0] = 3; res arr[0] = 3
origin arr[1] = 7; res arr[1] = 7
GETALL result after: 
origin arr[0] = 3; res arr[0] = 5
origin arr[1] = 7; res arr[1] = 5
[me@xiaoyehua ~/github/day11/test3]$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x000003e8 4          me         600        2         

[me@xiaoyehua ~/github/day11/test3]$ vim ipc_rm.c
[me@xiaoyehua ~/github/day11/test3]$ make
gcc ipc_rm.c -o ipc_rm
[me@xiaoyehua ~/github/day11/test3]$ ./ipc_rm 
[me@xiaoyehua ~/github/day11/test3]$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     


```
