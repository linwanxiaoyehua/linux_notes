# 最大监听数量
select结构体定义如下：
![name](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225165740041.png)

1. 将`fd_set`拷贝至`内核`
2. 0~`nfds-1`为文件描述符，进行循环，即轮询
3. 根据定义，最大监听数量为1024个文件描述符

