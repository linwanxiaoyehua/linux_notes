# signal设置信号处理行为，演示相同信号到来时，无法打断本信号的效果
```bash
[me@xiaoyehua ~/github/day12/test4]$ vim test.c 
[me@xiaoyehua ~/github/day12/test4]$ make
gcc test.c -o test
[me@xiaoyehua ~/github/day12/test4]$ ./test 
process begin
^Cbefore signum = 2
^C^Cafter signum = 2
before signum = 2
after signum = 2

```
