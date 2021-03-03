# 如果有进程正在使用一个信号量集合中的信号量，此时可以把信号量集合删除吗？写个程序验证你的想法。
```bash
[me@xiaoyehua ~/github/day11/test6]$ vim test.c
[me@xiaoyehua ~/github/day11/test6]$ vim ipc_rmid.c
[me@xiaoyehua ~/github/day11/test6]$ make
gcc ipc_rmid.c -o ipc_rmid
gcc test.c -o test
[me@xiaoyehua ~/github/day11/test6]$ ./test
[me@xiaoyehua ~/github/day11/test6]$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x000003e8 7          me         600        1         

[me@xiaoyehua ~/github/day11/test6]$ ./main
-bash: ./main: No such file or directory
[me@xiaoyehua ~/github/day11/test6]$ ./ipc_rmid 
[me@xiaoyehua ~/github/day11/test6]$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     


```
综上，会删除
