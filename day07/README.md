# 今日练习

1. 定义一个学生结构体类型struct student，里边含有学号，姓名，分数，定义结构体数组struct student s[3],给数组赋初值后，写入文件，然后通过lseek偏移到开头，然后再读取进行打印输出
2. 将标准输出重定向到log1文件，标准错误输出重定向到log2文件 有时间的同学看看syslog接口
3. 使用select实现即时聊天，要发送本机时间给对方显示，支持超时和退出机制
4. 实现同时读写的功能
5. 简要分析一下select的原理，它的时间复杂度和最大监听数量 

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

如果读写两端未建立连接，阻塞在`open函数`

### 是用两根管道进行全双工函数通信

#### CHAT1.C

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    int fdW = open(argv[2], O_wrONLY);
    puts("chat1");
    char buf[128] = {0};
    while(1){
    	memset(buf, 0, sizeof(buf));
    	read(fdr, buf, 127);
    	puts(buf);
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, 127);
   		write(fdw, buf, strlen(buf));
    }
    return 0;
}
```

#### CHAT2.C

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 3);
    int fdW = open(argv[1], O_wrONLY);
    int fdr = open(argv[2], O_RDONLY);
    puts("chat2");
    char buf[128] = {0};
    while(1){
    	memset(buf, 0, sizeof(buf));
    	read(fdr, buf, 127);
    	puts(buf);
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, 127);
   		write(fdw, buf, strlen(buf));
    }
    return 0;
}
```

## IO多路复用（转接）

`集合`：收集所有会导致阻塞的事件，然后等待这个集合，某个事件就绪，集合得到消息，提交给用户

### select函数

![image-20210225150958259](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225150958259.png)

`ndfs`：最大文件描述符+1 `readfds`：读集合 `write`：写集合

#### 使用方法

1. 设置一个等待集合
   1. `fd_set`定义一个集合
   2. `FD_ZERO`集合初始化

2. 把会发生阻塞的文件描述符加入集合（注册、监听、侦听），使用`FD_SET`接口
3. 使用`select`函数等待集合，等到集合中任意一个文件描述符就绪
4. 使用`FD_ISSET`判断某个文件描述符是否就绪，使用`if`进行判断是否进行后续操作

### 即时聊天代码示例

`初始化`、`监听`均需放在循环内

#### CHAT1.C

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    int fdW = open(argv[2], O_wrONLY);
    puts("chat1");
    fd_set rdset;
    while(1){
    	FD_ZERO(&rdset);
    	FD_SET(STDIN_FILENO, &rdset);
    	FD_SET(fdr, &rdset);
    	char buf[128];
    	select(fdr+1, &rdset, NULL, NULL, NULL);//永远等就是空指针
    	if(FD_ISSET(STDIN_FILENO, &rdset)){
        	puts("message from STDIN");
        	memset(buf, 0, sizeof(buf));
        	read(STDIN_FILENO, buf, sizeof(buf)-1);
        	write(fdw, buf, sizeof(buf));
        	puts(buf);
    	}
    	if(FD_ISSET(fdr, &rdset)){
        	puts("message from pipe");
        	memset(buf, 0, sizeof(buf)-1);
        	read(fdr, buf, sizeof(buf)-1);
    	    puts(buf);
    	}
    }
    close(fdr);
    close(fdw);
    return 0;
}
```

#### CHAT2.C

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 3);
    int fdW = open(argv[2], O_wrONLY);
    int fdr = open(argv[1], O_RDONLY);
    puts("chat2");
    fd_set rdset;
    while(1){
    	FD_ZERO(&rdset);
    	FD_SET(STDIN_FILENO, &rdset);
    	FD_SET(fdr, &rdset);
    	char buf[128];
    	select(fdr+1, &rdset, NULL, NULL, NULL);//永远等就是空指针
    	if(FD_ISSET(STDIN_FILENO, &rdset)){
        	puts("message from STDIN");
        	memset(buf, 0, sizeof(buf));
        	read(STDIN_FILENO, buf, sizeof(buf)-1);
        	write(fdw, buf, sizeof(buf));
        	puts(buf);
    	}
    	if(FD_ISSET(fdr, &rdset)){
        	puts("message from pipe");
        	memset(buf, 0, sizeof(buf)-1);
        	read(fdr, buf, sizeof(buf)-1);
    	    puts(buf);
    	}
    }
    close(fdr);
    close(fdw);
    return 0;
}
```

### 退出问题

1. write先关闭，read读一个`EOF`，`FD`一直就绪
2. read先关闭，出现崩溃，触发`SIG_PIPE`信号

#### 从管道识别EOF退出

```c
int ret = read(fdr, buf, sizeof(buf));
if(ret == 0){
    puts("over");
    break;
}
```

#### 从键盘识别EOF退出

```c
ift read(STDIN_FILENO, buf, sizeof(buf)-1);
if(ret == 0){
    puts("I quit");
    write(fdw, "you are a good person", num);
    break;
}
```

## select函数超时机制

![image-20210225162527243](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225162527243.png)

### 代码示例

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECH(argc, 3);
    int fdW = open(argv[2], O_wrONLY);
    int fdr = open(argv[1], O_RDONLY);
    puts("chat2");
    fd_set rdset;
    while(1){
    	FD_ZERO(&rdset);
    	FD_SET(STDIN_FILENO, &rdset);
    	FD_SET(fdr, &rdset);
    	char buf[128];
        //以下开始
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;
        int sret = select(fdr+1, &rdset, NULL, NULL, NULL);//永远等就是空指针
        if(sret == 0){
            puts("timeout!");
        }else{
            if(FD_ISSET(STDIN_FILENO, &rdset)){
        		puts("message from STDIN");
        		memset(buf, 0, sizeof(buf));
        		read(STDIN_FILENO, buf, sizeof(buf)-1);
        		write(fdw, buf, sizeof(buf));
        		puts(buf);
    		}
    		if(FD_ISSET(fdr, &rdset)){
        		puts("message from pipe");
        		memset(buf, 0, sizeof(buf)-1);
        		read(fdr, buf, sizeof(buf)-1);
    	    	puts(buf);
    		}
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}
```

## 写入阻塞

管道中挤压数据过多，无法继续写入，`O_RDWR`：非阻塞方式建立读写端，`O_NONBLK`同理（遵循`posix`规则）

### 示例代码

```c
#include <func.h>
int main(int argc, char *argv[]){
    ARGS_CHECK(args, 2);
    int fdr = open(argv[1], O_RDWR);
    int fdw = open(argv[1], O_RDWR);
    puts("established");
    fd_set rdset;
    fd_set wrset;
    int cnt = 0;
    char wrbuf[4096] = {0};
    char rdbuf[4096] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(&rdset);
        FD_SET(&wrset);
        select(fdw+1, &rdset, &wrset, NULL, NULL);
        if(FD_ISSET(fdw, &wrset)){
            printf("cnt = %d", ++cnt);
            write(fdw, wrbuf, 4096);
            puts("write success");
        }
        if(FD_ISSET(fdr, &rdet)){
            read(fdr, rdbuf, 2048);
            puts("read success");
        }
    }
    return 0;
}
```

### 出错问题

```c
if(FD_ISSET(fdw, &wrset)){
            printf("cnt = %d", ++cnt);
            write(fdw, wrbuf, 8192);//此处出错
            puts("write success");
}
```

`pipe`存储在内核管道缓冲区，`ulimit -a`可查询该缓冲区大小，写就绪就是内核管道缓冲区为空

写入操作大小不能超过内核管道缓冲区大小

## select函数原理

![image-20210225165740041](https://gitee.com/xiao_yehua/pic/raw/master/image-20210225165740041.png)

1. 将`fd_set`拷贝至`内核`
2. 0~`nfds-1`为文件描述符，进行循环，即轮询，另外一个接口为`epoll`（采用红黑树进行存储，查找复杂度为O(logN)；