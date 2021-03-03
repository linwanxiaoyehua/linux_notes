# 使用计数信号量，实现生产者消费者模型
```bash
[me@xiaoyehua ~/github/day11/test5]$ vim producer_cosumer.c
[me@xiaoyehua ~/github/day11/test5]$ make
gcc producer_cosumer.c -o producer_cosumer
[me@xiaoyehua ~/github/day11/test5]$ ./producer_cosumer 
I'm producer, before produce, space = 6, goods = 0
produce goods
I'm producer, after produce, space = 5, goods = 1
I'm cosumer, before cosume, space = 5, goods = 1
buy goods
I'm cosumer, after cosume, space = 6, goods = 0
I'm producer, before produce, space = 6, goods = 0
produce goods
I'm producer, after produce, space = 5, goods = 1
I'm producer, before produce, space = 5, goods = 1
produce goods
I'm producer, after produce, space = 4, goods = 2
I'm cosumer, before cosume, space = 4, goods = 2
buy goods
I'm cosumer, after cosume, space = 5, goods = 1
I'm producer, before produce, space = 5, goods = 1
produce goods
I'm producer, after produce, space = 4, goods = 2
I'm producer, before produce, space = 4, goods = 2
produce goods
I'm producer, after produce, space = 3, goods = 3
I'm cosumer, before cosume, space = 3, goods = 3
buy goods
I'm cosumer, after cosume, space = 4, goods = 2
I'm producer, before produce, space = 4, goods = 2
produce goods
I'm producer, after produce, space = 3, goods = 3
^C

```
