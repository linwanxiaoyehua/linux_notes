# 捕捉SIGINT并设置信号处理行为，把默认的终止进程的处理行为改为打印，打印捕捉到的信号的值
```bash
[me@xiaoyehua ~/github/day12/test1]$ vim sigint.c
[me@xiaoyehua ~/github/day12/test1]$ make
gcc sigint.c -o sigint
[me@xiaoyehua ~/github/day12/test1]$ ./sigint 
process begin
^Csignum = 2
^Csignum = 2
^Csignum = 2
^Csignum = 2
^Csignum = 2
^_^H^\Quit (core dumped)

```
