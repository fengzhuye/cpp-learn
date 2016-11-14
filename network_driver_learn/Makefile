#hello.ko  
  
obj-m += hello.o     #指定编译模块名称，会自动寻找hello.c  
CURRENT_PATH:=$(shell pwd)  
LINUX_KERNEL:=$(shell uname -r)  

#EXTRA_CFLAGS = -std=c99
  
LINUX_KERNEL_PATH:=/usr/src/linux-headers-3.4.6-xenomai-2.6.3         #内核源码目录  
#LINUX_KERNEL_PATH:=/usr/src/linux-headers-3.13.0-35
  
all:  
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules     #C进入内核目录读取Makefile，M表明后回到当前目录读取Makefile  
  
clean:  
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean  
