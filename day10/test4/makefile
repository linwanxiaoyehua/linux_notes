CC:=gcc
srcs:=$(wildcard *.c)#1.c 2.c 3.c
exe:=$(patsubst %.c,%,$(srcs))#1 2 3
all:$(exe)
%:%.c
	$(CC) $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) $(exe)
rebuild:clean all
