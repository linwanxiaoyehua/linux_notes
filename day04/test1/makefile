CC:=gcc #将预定义变进行重定义
exe:=main #设定目标项自定义变量
objs:=main.o sub.o #设定依赖项自定义变量
$(exe):$(objs)
	$(CC) $^ -o $@ #自动变量，$^位依赖项，$@为目标项
main.o:main.c
	$(CC) -c $^ -o $@
sub.c:sub.o
	$(CC) -c $^ -o $@
.PHONY:clean rebulid
rebuild:clean main
clean:
	$(RM) $(exe) $(objs)
