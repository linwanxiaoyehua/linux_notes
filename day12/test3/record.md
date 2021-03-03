# signal设置信号处理行为，演示不同信号到来时，后来的信号会打断原有信号的信号处理函数结果
```bash
[me@xiaoyehua ~/github/day12/test3]$ vim test.c 
[me@xiaoyehua ~/github/day12/test3]$ make
gcc test.c -o test
[me@xiaoyehua ~/github/day12/test3]$ ./test 
process begin
^Cbefore signum = 2
^C^\before signum = 3
after signum = 3
after signum = 2
before signum = 2
after signum = 2

```
