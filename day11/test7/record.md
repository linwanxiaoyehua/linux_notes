# 编写一组程序，创建消息队列，实现以下的功能：
    1：可以按照不同的mtype类型去发送消息，接收消息。
    2：可以无差别的接收整个队列中的消息。
    3：不阻塞的接收消息。
    4：删除消息队列。
```bash
[me@xiaoyehua ~/github/day11/test7]$ ./test1
[me@xiaoyehua ~/github/day11/test7]$ ./test2
type = 1, msg = 0
[me@xiaoyehua ~/github/day11/test7]$ ./test3
[me@xiaoyehua ~/github/day11/test7]$ ipcs

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     

[me@xiaoyehua ~/github/day11/test7]$ 

```
