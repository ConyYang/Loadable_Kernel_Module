obj-m := mod.o

all:
	make -C /usr/src/linux-headers-`uname -r` M=`pwd` modules
