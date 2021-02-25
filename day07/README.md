# 昨日回顾

不带文件缓冲区的I/O，打开文件描述符

![image-20210225095215666](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225095215666.png)

`open`（使用三个参数为创建文件）、`close`、`read`、`write`都为系统调用

`文件空洞`文件大小可能会大于实际占用空间

`ftruncate`文件截断

`mmap`建立磁盘与内存的映射关系，存储在堆(相关参数：`addr`：NULL， `size`：页大小的整数倍，`prot`：读写权限，`flag`：例如MAP_SHARED，`文件描述符`，`偏移量`)

# 今日内容

## lseek函数

![image-20210225095643138](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225095643138.png)

### 函数实例

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    lseek(fd, 40960, SEEK_SET);//偏移过多会产生文件空洞
    write(fd, 1, "1");
    close(fd);
    return 0;
}
```

## 文件流与文件描述符的关系

文件流`依赖于`文件描述符，文件流中存在成员`int _fileno（文件描述符）`

### 示例代码

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    FILE *fp = fopen(argv[1], "r+");
    ERROR_CHECK(fp, NULL, "fopen");
    write(3. "howareyou", 9);//3为fileno
    int fd = fp->_fileno;
    write(fd, "howareyou", 9);//等同于上句
    fclose(fp);
    return 0;
}
```

### fileno函数

从`文件流`中获取`文件描述符`

```c
FILE *fp = fopen(argv[1], "r+");
int fd = fileno(fp);
```

## 文件流的缓冲类型

### 全缓冲

例如`磁盘文件`

### 行缓冲

例如`stdin`、`stderr`

### 不缓存

例如`stderr`

## 文件描述符的复制

不同的文件秒描述符指向`同一文件`，**`共享读写位置`**

### 函数原型

![image-20210225102734598](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225102734598.png)

### dup函数测试代码

不同的文件秒描述符指向`同一文件`，**`共享读写位置`**

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int oldfd = open(argv[1], O_RDWR);
    ERROR_CHECK(oldfd, -1, "open");
    printf("oldfd = %d\n", oldfd);
    int newfd = dup(oldfd);
    printf("newfd = %d\n", newfd);
    write(oldfd, "hello", 5);
    write(newfd, "world", 5);
    close(newfd);
    close(oldfd);
    return 0;
}
```

`close`函数只会断掉指向，会使用到`引用计数`

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int oldfd = open(argv[1], O_RDWR);
    ERROR_CHECK(oldfd, -1, "open");
    printf("oldfd = %d\n", oldfd);
    int newfd = dup(oldfd);
    printf("newfd = %d\n", newfd);
    write(oldfd, "hello", 5);
    close(oldfd);
    int ret = write(newfd, "world", 5);
    ERROR_CHECK(ret, -1, "write");
    close(newfd);
    return 0;
}
```

### 使用dup函数实现文件重定向

```
printf-->stdout-->FO-->
fprintf(stdout)-->FO-->
将stdout定向到磁盘
```

**实现步骤**

1. open打开文件
2. close(1)
3. dup(3)

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(oldfd, -1, "open");
    printf("\n");//清空内部内容，需要先打印换行
    close(STDOUT_FILENO);
    int newfd = dup(fd);//newfd == 1
    ERROR_CHECK(newfd, -1, "newfd");
    printf("newfd = %d\n", newfd);
    printf("can yous see me?");
    close(fd);
    close(newfd);
    return 0;
}
```

### 使用dup2函数实现文件重定向

![image-20210225111515439](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225111515439.png)

**`newfd`需要自己主动设置**

**步骤**

1. dup2(STDOUT_FILENO, 10)

2. a)close(1), dup(3)

   b)dup2(3, 1)

3. a)close(1), dup(10)

   b)dup2(10, 1);

![image-20210225111905315](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225111905315.png)

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    dup2(STDOUT_FILENO, 10);
    dup2(fd, STDOUT_FILENO);
    printf("You cant't see me\n");
    dup2(10, STDOIT_FILENO);
    printf("You can see me\n");
    close(fd);
    close(10);
    return 0;
}
```

## 管道

`有名管道`(named pipe/FIFO)，通过管道在两个进程间通信，存储在`文件系统`，传输数据不经过磁盘

管道定义为`半双工`，实际可以`全双工`，使用两根管道实现全双工

管道`不能长期存储数据`

| 传输方式 | 功能                                 |
| -------- | ------------------------------------ |
| 单工     | 永远只能A->B                         |
| 半双工   | 有时A->B，有时B->A，但是不能同时进行 |
| 全双工   | 可以同时A<-->B                       |

### mkfifo命令创建管道

![image-20210225113404177](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225113404177.png)

```bash
mkfifo 1.pipe #创建管道
echo hello > 1.pipe #写入pipe
cat 1.pipe #读取pipe
#只要有一端没有完成管道就会阻塞
```

### 使用单根管道进行函数通信

#### 读取端

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 2);
    int fdr = open(argv[1], O_RDONLY);
    puts("open");
    ERROR_CHECK(fdr, -1, "open");
    char buf[128] = {0};
    read(fdr, buf, 127);
    puts("read");
    puts(buf);
    close(fd);
    return 0;
}
```

#### 写入端

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 1);
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    char buf[128] = {0};
    write(fdw, "hello", 5);
    close(fd);
    return 0;
}
```

#### 注意

如果读写两端未建立，阻塞在`open函数`