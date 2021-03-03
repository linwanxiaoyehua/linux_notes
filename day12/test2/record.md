# 在第一题的基础上，再通过signal函数还会2号信号默认的处理行为（终止）
```bash
[me@xiaoyehua ~/github/day12/test2]$ vim sigint.c 
[me@xiaoyehua ~/github/day12/test2]$ make
gcc sigint.c -o sigint
[me@xiaoyehua ~/github/day12/test2]$ ./sigint 
process begin
^Csignum = 2

```
