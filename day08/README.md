# 操作系统历史

## 批处理系统（batch）

### 存在的问题

CPU速度远远大于I/O设备

## 多道程序设计

多个任务同时驻留在内存上

### 存在的问题

1. 需要人为分配地址
2. 无法对鼠标等操作回应

## 分时操作系统

多个程序交替执行，只要时间间隔够小，用户看来多个任务是同时进行的，`并发`、`并行`

## 进程

### **特点**

1. 虚拟CPU（对单个进程来说，CPU专门为其服务）
2. 虚拟内存（虚拟地址空间、进程地址空间）
3. 一份文件可以生成多个不同进程
4. 进程运行过程中可以更换程序文件

### 定义

用户眼中：进程是动态执行过程

OS角度：进程是分配资源的基本单位，`解耦`

# 虚拟CPU

`调度器`：只运行在内核中，负责切换进程，其本身是一个特殊进程

## 时间片轮转法（linux为完全公平调度CFS）

### 优先级相同

![image-20210226100902900](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226100902900.png)

### 进程的三种状态

![image-20210226101139182](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226101139182.png)

# 进程的相关指令

## 查看CPU信息

```bash
cd usr/proc
cat cpuinfo
```

## 查看进程

```bash
ps -elf
```

## 查看调度策略

```bash
sched
```



# 进程控制块（PCB）

内核用来管理进程的`数据结构`（struct task_struct)，定义在sched.h头文件

![image-20210226103536579](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226103536579.png)

# pid ppid

用户处理进程使用pid，进程具有`亲缘关系`

进程0会被boot loader启动，进程0会启动1进程`init`进程（新版本称为`system`），也会启动2进程（页面守护进程，内存管理进程），其余进程会被1进程启动，比如shell（单用户），对于多用户为`tty`进程，网络进程为`pts`，`tty`进程会启动`bash`进程

进程为`树形结构`

## 函数接口

![image-20210226110302049](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226110302049.png)

## 测试代码

```c
#include <func.h>
int mian(){
    pit_t pid = getpid();
    pid_t ppid = getppid();
    printf("pid = %d ppid = %d", pid, ppid);
    return 0;
}
```

# uid gid euid egid

进行权限控制

`uid`：真实uid

`euid`：有效uid，系统决定是否拥有权限

uid与euid只与执行者有关

## 函数接口

![image-20210226111820912](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226111820912.png)

## 测试代码

```c
#include <func.h>
int mian(){
    printf("uid = %d euid = %d", getuid(), geteuid());
    return 0;
}
```

## 文件特殊权限

更改有效用户id（euid）去超过权限，比如passwd，sudo

文件特殊权限`s`（需要为可执行文件）：程序执行时会修改euid为文件拥有者，命令`chmod u+s`，对于文件执行时需要：

1. 拥有`s`权限
2. 拥有user的执行权限

```c
#include <func.h>
int main(int argc, char *argv[]){
    
}
```

文件特殊权限sticky，只对目录文件生效，显示`t`，要求：

1. 拥有t权限
2. 拥有o的w和x权限
3. 可以创建文件，可以删除自己的文件，不可以删除别人的文件

## 函数原型

1. 拥有group执行权限
2. g+s

![image-20210226114236819](https://gitee.com/xiao_yehua/pic/raw/master/image-20210226114236819.png)

## 测试代码

```c
#include <func.h>
int mian(){
    printf("gid = %d egid = %d", getgid(), getegid());
    return 0;
}
```

