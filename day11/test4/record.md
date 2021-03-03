# 使用二进制信号量，改写昨天的程序，让两个进程对同一个数加10000000次后，显示正确结果
```bash
[me@xiaoyehua ~/github/day11/test4]$ vim add.c
[me@xiaoyehua ~/github/day11/test4]$ make
gcc add.c -o add
[me@xiaoyehua ~/github/day11/test4]$ ./add
p[0] = 20000000

```
